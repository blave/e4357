#include "mbed.h"
#include "ble_mini.h"
#include "TMP006.h"									// temp sensor support
#define Address 0x80								// temp sensor address: ADR0 = ADR1 = GND >>> address = 0x80

DigitalOut one28(p21), sixty4(p19), thirty2(p18), sixteen(p17);		// BCD outputs for HP hexadecimal 5x7 pixel displays
DigitalOut eight(p16), four(p15), two(p14), one(p13);
DigitalOut myLed1(LED1), myLed2(LED2), myLed3(LED3), myLed4(LED4);
DigitalOut greenLED(p26), redLED(p25);

AnalogIn bendy( p20 );							// set pin to read flex sensor/resistor voltage divider value (sensor & resistor: 10K ohms)
TMP006 sensor( p9, p10, Address ); 	// assign I2C pins and I2C address that temp sensor is connected to (SDA, SCL, address)
Serial pc( USBTX, USBRX );					// USB serial port "pins"
Serial bluetooth( p28, p27 );				// pins for BLE Mini board 

int main()
{
  float cent, fahr, previousTemp, newTemp;
	char charHpNumberScaled[10], charCent[10];	// Character arrays to hold values so that "puts()" can be used to print to BLE
	char buf;																		// Buffer for holding incoming bluetooth traffic
  int hpNumberScaled;													// hpNumberScaled is the flex sensor's value scaled to 00 - ff (hex)
	int previousFlex = 0, newFlex = 0;
  
  bluetooth.baud( 57600 );										// Set bluetooth instance's baud rate to that of the BLE Mini board
  
  while(1) 																		// Loop forever
	{
    //******* Flex sensor handling *************************//
		previousFlex = bendy;
		hpNumberScaled = bendy * 255;					  								// Scale flex sensor reading to the range of the 2 HP hex displays' range
    sprintf( charHpNumberScaled, "F%df", hpNumberScaled );	// Convert flex sensor values to strings so that "puts()" can be used
		                                                        // and pad strings with characters that identify what they contain
		bluetooth.puts( charHpNumberScaled );									  // Print to BLE Mini
		//pc.printf( "%c " , charHpNumberScaled );
		//pc.puts( charHpNumberScaled );
		//pc.puts( "\n\r" );
		
		//******* Temperature sensor handling ******************//
		previousTemp = cent;
		cent = sensor.readObjTempC( Address );									// Read IR temp sensor's value
		sprintf( charCent, "T%.ft", cent );		                  // Convert temperature value to string so that "puts()" can be used
		bluetooth.puts( charCent );															// Write to BLE UART
		//pc.printf( "%.1f " , cent );
		//pc.puts( charCent );
		//pc.puts( "\n\r" );

		//******* Print to USB UART console ********************//
		newTemp = cent;
		newFlex = bendy;
		if( newFlex < previousFlex  ||  newFlex > previousFlex ||		// Only print to USB console if
			( newTemp < previousTemp  ||	newTemp > previousTemp ) )	// temperature and/or flex sensor value 
																																// has changed since last loop																																			
		{ 
			pc.printf( "Temperature: %.fC / %.fF    Flex Sensor = %d / 0x%x\r \n", cent, fahr = (cent * 1.8) + 32, hpNumberScaled, hpNumberScaled);
		}

		//******* Read data transmitted from iDevice to control the 4 on-board mbed LEDs and display it on the HP hexadecimal displays ********//
		if( bluetooth.readable() )
		{
				buf=bluetooth.getc();
				
				if(buf==ON_INTERNEL_LED1)
				{
					myLed1=1;
				}
				if(buf==OFF_INTERNEL_LED1)myLed1=0;
				
				if(buf==ON_INTERNEL_LED2)myLed2=1;
				if(buf==OFF_INTERNEL_LED2)myLed2=0;            
				
				if(buf==ON_INTERNEL_LED3)myLed3=1;
				if(buf==OFF_INTERNEL_LED3)myLed3=0;            
				
				if(buf==ON_INTERNEL_LED4)myLed4=1;
				if(buf==OFF_INTERNEL_LED4)myLed4=0;
				
				if(buf==0x14)
				{ 
					buf = bluetooth.getc();
					//pc.printf( " %d", buf );
					
					one28   = (int)buf & 128;			// send BCD-encoded value of iDevice "Display" slider to the 2 HP displays' BCD decoders
					sixty4  = (int)buf & 64;
					thirty2 = (int)buf & 32;
					sixteen = (int)buf & 16;
					eight   = (int)buf & 8;
					four    = (int)buf & 4;
					two     = (int)buf & 2;
					one     = (int)buf & 1;
					
					if( (int)buf < 32 )						// Light green or red LEDs if the iDevice slider is all the way to the left or right)
					{
						greenLED = 1;
					}
					else if( (int)buf > 220 )
					{
						redLED = 1;
					}
					else
					{
						greenLED = 0;
						redLED = 0;
					} // end red/green LED conditionals
				} // end of if(buf==0x14)
		} // end of if(bluetooth.readable())
	wait(0.05);	
	}
} // end of main()


