#include "mbed.h"
#include "ble_mini.h"

Serial pc(USBTX, USBRX); // tx, rx
Serial bluetooth(p28,p27);
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
DigitalOut RedLed(p18);
PwmOut PWM1(p21);

AnalogIn bendy(p20);

char buf[10];
float brightness = 0.0;



int main() {
    int i=0;
	 int hpNumber1, hpNumberScaled;
    //set mbed baud rate the same as BLE mini baud rate
    bluetooth.baud(57600);
    //simple polling demonstrate serial communication
    while(1) {
				hpNumber1 = bendy;										// read flex sensor's resistance
				hpNumberScaled = bendy * 255;
			  char dave[20];
				sprintf(dave, "F%df", hpNumberScaled);
				pc.printf(dave, " F%df ");
				bluetooth.puts(dave);
        if(bluetooth.readable()) {
					bluetooth.puts(dave);
					pc.puts("HELLO");
            buf[i]=bluetooth.getc();
            if(buf[i]==ON_INTERNEL_LED1)
						{
							myled1=1;
						}
            if(buf[i]==OFF_INTERNEL_LED1)myled1=0;
					  
            if(buf[i]==ON_INTERNEL_LED2)myled2=1;
            if(buf[i]==OFF_INTERNEL_LED2)myled2=0;            
            
            if(buf[i]==ON_INTERNEL_LED3)myled3=1;
            if(buf[i]==OFF_INTERNEL_LED3)myled3=0;            
            
            if(buf[i]==ON_INTERNEL_LED4)myled4=1;
            if(buf[i]==OFF_INTERNEL_LED4)myled4=0;
            
            if(buf[i]==0x10) RedLed=1;
            if(buf[i]==0x11) RedLed=0;
            
            if(buf[i]==0x12)
            {  PWM1.period(0.010);  // set PWM period to 10 ms
              PWM1=0.1; }
            if(buf[i]==0x13) 
            {  PWM1.period(0.010);  // set PWM period to 10 ms
              PWM1=0.8;}
            
            if(buf[i]==0x14) 
            {buf[i]=bluetooth.getc();
           // int data = buf[i]-'0';
            brightness = buf[i]+0.001;
            PWM1.period(0.010);  // set PWM period to 10 ms
              PWM1=brightness/255; }
            
            i++;  
        }
        
        if(i==10)i=0;
        wait(0.5);
    }
}



