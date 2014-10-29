#include "mbed.h"

DigitalIn inputOne(p12);								// PIR input
DigitalIn switch1(p5), switch2(p6);
DigitalOut one28(p20), sixty4(p19), thirty2(p18), sixteen(p17);
DigitalOut eight(p16), four(p15), two(p14), one(p13);
DigitalOut myled1(LED1), myled2(LED2), myled3(LED3), myled4(LED4);
DigitalOut red(p25), green(p26);
DigitalOut rate(p11);
PwmOut myPwm(p21);

int main()
{
	myPwm.period_us(500);
	
	while(1)
	{
		for(unsigned int i = 0; i < 256; i++)
		{
			if(inputOne || switch1 || switch2)
			{
				for(unsigned int j = 0; j < 4; j++)
				{
					red = 0;
					green = 1;
					wait(0.09);
					green = 0;
					red = 1;
					wait(0.09);
				}
				red = green = 0;
				break;
			}
			
			if(i < 128)
				myPwm   = i * 0.004;
			else
				myPwm   = 1 - (i * 0.004);
			
			one28   = myled4 = i & 128;
			sixty4  = myled3 = i & 64;
			thirty2 = myled2 = i & 32;
			sixteen = myled1 = i & 16;
			eight = i & 8;
			four  = i & 4;
			two   = i & 2;
			one   = i & 1;
			rate = !rate;			// output to monitor outer "for" loop frequency
			wait(0.063);				// 0.063 results in approx. 1 second MSD counting
		}
	}

}
