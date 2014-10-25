
// function prototypes
void delay(void);
 
//Define addresses of digital i/o control registers, as pointers to volatile data
#define FIO2DIR0 (*(volatile unsigned char *)(0x2009C040))
#define FIO2PIN0 (*(volatile unsigned char *)(0x2009C054))
#define FIO0PIN0 (*(volatile unsigned char *)(0x2009C014))
 
int main()
{
    FIO2DIR0=0xFF;     // set port 2, lowest byte to output
    while(1) {
        for (int i=1; i<=3; i++) {
            FIO0PIN0 |= 0x02;       // set port 2 pin 1 high (mbed pin 25)
            delay();
            FIO0PIN0 &= ~0x02;      // set port 2 pin 1 low
            delay();
        }
 
    }
}
//delay function
void delay(void)
{
    int j;                      //loop variable j
    for (j=0; j<1000000; j++) {
        j++;
        j--;                      //waste time
    }
}
