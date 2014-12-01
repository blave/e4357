#include "mbed.h"
#include "ble_mini.h"
#include "TMP006.h"							// temp sensor support
#define Address 0x80						// temp sensor address: ADR0 = ADR1 = GND >>> address = 0x80

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
  float cent, fahr;
	char charHpNumberScaled[10], charCent[10];
	char buf;													// buffer for holding incoming bluetooth traffic
  int hpNumberScaled;								// hpNumberScaled is the flex sensor's value scaled to 00 - ff (hex)
  
  bluetooth.baud( 57600 );					// set bluetooth instance's baud rate to that of the BLE Mini board
  
  while(1) 
	{
    cent = sensor.readObjTempC( Address );									// Read IR temp sensor's value
		hpNumberScaled = bendy * 255;					  								// Scale flex sensor reading to the range of the 2 HP hex displays' range
    sprintf( charHpNumberScaled, "F%df", hpNumberScaled );	// Convert flex & temp sensors' values to strings so that puts() can be used
		sprintf( charCent, "T%.ft", cent );											// Pad strings with characters that identify what they contain
		bluetooth.puts( charHpNumberScaled );										// Print to BLE Mini
		bluetooth.puts( charCent );
		//pc.printf( "Temperature: %.fC / %.fF    Flex Sensor = %d / 0x%x\r \n", cent, fahr = (cent * 1.8) + 32, hpNumberScaled, hpNumberScaled);		// print to USB console
    //pc.printf( "%.1f " , cent );
		//pc.puts( charHpNumberScaled );
		//pc.puts( "\n\r" );
		//pc.puts( charCent );
		
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
					
					one28   = (int)buf & 128;			// send BCD codes of the flex sensor's value to the 2 HP displays' BCD decoders
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
	wait(0.4);	
	}
} // end of main()


