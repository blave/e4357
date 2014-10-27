#include "mbed.h"

DigitalOut eight(p20), four(p19), two(p18), one(p17);
DigitalOut myled1(LED1), myled2(LED2), myled3(LED3), myled4(LED4);
PwmOut myPwm(p21);

int main()
{
	
	while(1)
	{
		for(unsigned int i = 0; i < 16; i++)
		{
			myPwm = i * 0.005;
			eight = myled1 = i & 8;
			four  = myled2 = i & 4;
			two   = myled3 = i & 2;
			one   = myled4 = i & 1;
			wait(0.4);
		}
	}

}
