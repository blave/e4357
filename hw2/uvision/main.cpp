#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

int main() {
    int i = 0;
    while(1) {  
        myled1 = i & 1;
        myled2 = i & 2;
        myled3 = i & 4;
        myled4 = i & 8;
        wait(0.2);
        i++;
    } 
}
