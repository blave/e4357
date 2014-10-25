/*Program Example 14.1: Sets up a digital output pin using control registers, and flashes an led.                                      
                                                                         */
// function prototypes                                   
void delay(void);
 
//Define addresses of digital i/o control registers, as pointers to volatile data
#define FIO2DIR0       (*(volatile unsigned char *)(0x2009C040)) 
#define FIO2PIN0       (*(volatile unsigned char *)(0x2009C054))
 
int main() {
  FIO2DIR0=0xFF;     // set port 2, lowest byte to output
  while(1) {
    FIO2PIN0 |= 0x01;     // OR bit 0 with 1 to set pin high
    delay();
    FIO2PIN0 &= ~0x01;   // AND bit 0 with 0 to set pin low
    delay();
  }
}
//delay function
void delay(void){                                         
  int j;                      //loop variable j
  for (j=0;j<1000000;j++) {     
    j++;
    j--;                      //waste time
  }
}



//#include "mbed.h"
//DigitalOut eight(p20), four(p19), two(p18), one(p17);				// BCD outputs to HP display
//DigitalOut myled1(LED1), myled2(LED2), myled3(LED3), myled4(LED4);
//PwmOut myPwm(p21);
// 
////Define addresses of digital i/o control registers, as pointers to volatile data
//#define FIO0DIR0 (*(volatile unsigned char *)(0x2009C000)) // input port
//#define FIO0PIN0 (*(volatile unsigned char *)(0x2009C014))
//#define FIO2DIR0 (*(volatile unsigned char *)(0x2009C040)) // output port
//#define FIO2PIN0 (*(volatile unsigned char *)(0x2009C054))
//#define PINMODE0 (*(volatile unsigned long *)(0x4002C040)) // for controlling pullup/down
// 
//int main() {
//	FIO0DIR0=0x00;
//  FIO2DIR0=0xFF;     // set port 2, lowest byte to output
//	PINMODE0 = PINMODE0 & 0xFFFFFFFF;		// this should be setting a pulldown resistor... not sure that it is though.
//  while(1) {
//    //FIO2PIN0 |= 0x01;  // OR bit 0 with 1 to set pin high (green)
//		FIO2PIN0 &= ~0x02;   // set port 2 pin 1 low (red)
//    wait(0.8);
//    //FIO2PIN0 &= ~0x01; // AND bit 0 with 0 to set pin low (green)
//		FIO2PIN0 |= 0x02;    // set port 2 pin 1 high (mbed pin 25) (red)
//		
//		for(unsigned int i = 0; i < 16; i++)
//		{
//			if((FIO0PIN0 & 0x01) == 1)	// if pin mbed pin9 is high,
//			{
//				FIO2PIN0 |= 0x01;					// turn on green LED (pin26) for 4 seconds
//				wait(1.0);
//				FIO2PIN0 &= ~0x01;
//			}
//			myPwm = i * 0.005;					// Increase brightness of LED as 'i' counts up
//			eight = myled1 = i & 8;			// Show BCD code on LEDs and show the corresponding
//			four  = myled2 = i & 4;			// number on HP hexadecimal display
//			two   = myled3 = i & 2;
//			one   = myled4 = i & 1;
//			wait(0.4);
//		}
//    //delay();
//  }
//}

