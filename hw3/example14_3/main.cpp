/* Program Example 14.3: Uses digital input and output using control registers, and flashes an LED. LEDS connect to mbed pins 25 and 26. Switch input to pin 9.
                                          */
// function prototypes                                   
void delay(void);
//Define Digital I/O registers
#define FIO0DIR0 (*( volatile unsigned char *)(0x2009C000))
#define FIO0PIN0 (*( volatile unsigned char *)(0x2009C014))
#define FIO2DIR0 (*(volatile unsigned char *)(0x2009C040)) 
#define FIO2PIN0 (*(volatile unsigned char *)(0x2009C054))
//some variables
char a;
char b;
char i;
 
int main() {
   FIO0DIR0=0x00;             // set all bits of port 0 byte 0 to input 
   FIO2DIR0=0xFF;             // set port 2 byte 0 to output
   while(1) {
     if (FIO0PIN0&0x01==1){   // bit test port 0 pin 0 (mbed pin 9)
       a=0x01;                // this reverses the order of LED flashing
       b=0x02;                // based on the switch position
     } 
     else {    
       a=0x02;
       b=0x01;
     }
     FIO2PIN0 |= a;        
     delay();
     FIO2PIN0 &= ~a;                    
     delay();
             
     for (i=1;i<=3;i++){
       FIO2PIN0 |= b;    
       delay();
       FIO2PIN0 &= ~b;             
       delay();
     }
   }                          //end while loop
}
 
void delay(void){            //delay function.
    int j;                      //loop variable j
    for (j=0; j<1000000; j++) {
        j++;
        j--;                      //waste time
    }
}