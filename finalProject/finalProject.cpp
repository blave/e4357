#include "mbed.h"
#include "TMP006.h"						// temp sensor support
#define Address 0x80					// temp sensor address

Serial pc(USBTX, USBRX);			// USB serial port "pins"
Serial bluetooth(p28, p27);		// pins for BLE Mini board

DigitalOut one28(p21), sixty4(p19), thirty2(p18), sixteen(p17);		// BCD outputs for HP hexadecimal 5x7 pixel displays
DigitalOut eight(p16), four(p15), two(p14), one(p13);
DigitalOut myLed1(LED1), myLed2(LED2), myLed3(LED3), myLed4(LED4);

AnalogIn bendy(p20);					// set pin to read flex sensor/resistor voltage divider value
 
TMP006 sensor(p9, p10, Address); 	// assign I2C pins that temp sensor is connected to
 
int main()
{
  float cent, fahr;

  int hpNumber1, hpNumberScaled;	// hpNumberScaled is the flex sensor's value scaled to 00 - ff (hex)
  
  bluetooth.baud(57600);					// set bluetooth instance's baud rate to that of the BLE Mini board
  
  while(1) 
  {
    cent = sensor.readObjTempC(Address);	// read IR temp sensor's value
    hpNumber1 = bendy;										// read flex sensor's resistance
		hpNumberScaled = bendy * 255;					// scale flex sensor reading to the range of the 2 HP hex displays' range
    pc.printf("Temperature: %.fC; %.fF    Bendy = %x / %x\r \n", cent, fahr = (cent * 1.8) + 32, hpNumberScaled);		// print to USB console
    bluetooth.printf("Temp: %.fC; %.fF    Bendy = %x\r \n* * *\n", cent, fahr, hpNumberScaled);											// print to BLE Mini
		myLed1 = !myLed1;
    
		one28   = hpNumberScaled & 128;			// send BCD codes of the flex sensor's value to the 2 HP displays' BCD decoders
		sixty4  = hpNumberScaled & 64;
		thirty2 = hpNumberScaled & 32;
		sixteen = hpNumberScaled & 16;
		eight = hpNumberScaled & 8;
    four  = hpNumberScaled & 4;
    two   = hpNumberScaled & 2;
    one   = hpNumberScaled & 1;

    wait(0.2);
  }
}


