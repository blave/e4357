#include "mbed.h"

DigitalIn inputOne(p12);
DigitalOut one28(p20), sixty4(p19), thirty2(p18), sixteen(p17);
DigitalOut eight(p16), four(p15), two(p14), one(p13);
DigitalOut myled1(LED1), myled2(LED2), myled3(LED3), myled4(LED4);
DigitalOut red(p25), green(p26);
PwmOut myPwm(p21);

int main()
{
	myPwm.period_us(5);
	
	while(1)
	{
		for(unsigned int i = 0; i < 256; i++)
		{
			if(inputOne)
			{
				for(unsigned int j = 0; j < 4; j++)
				{
					red = 0;
					green = 1;
					wait(0.08);
					green = 0;
					red = 1;
					wait(0.08);
				}
				red = green = 0;
				break;
			}
			
			myPwm   = i * 0.004;
			one28   = myled1 = i & 128;
			sixty4  = myled2 = i & 64;
			thirty2 = myled3 = i & 32;
			sixteen = myled4 = i & 16;
			eight = myled1 = i & 8;
			four  = myled2 = i & 4;
			two   = myled3 = i & 2;
			one   = myled4 = i & 1;
			wait(0.1);
		}
	}

}
