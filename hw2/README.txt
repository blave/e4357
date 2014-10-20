Total Hours Spent: 2.0

1. NOTE Before receiving this assignment, I had changed my HelloWorld.c to the following... so the 
counts will be, in some cases, slightly different than the stock file.

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


part 1.

-----
NOTE TO DAVE: this shell script gives different # of files: 
find -maxdepth 10 -type d | while read -r dir; do printf "%s:\t" "$dir"; find "$dir" -type f | wc -l; done
it comes up with 84 (gcc) and 86 (uvision).
BUT "find * | wc -l" done at each tree's root gives yet another number (70 for uvision)!

# of source lines:	
find . -name '*.h' | xargs wc -l
find . -name '*.cpp' | xargs wc -l
-----

# text files :	gcc_arm => (77 - 6) = 71 (subtracting object and library files)
				uvision => (77 - 7) = 70     "       "       "
				note:	some files are observed to be binary but are not object or library files, e.g.
						\gcc_arm\.hg\dirstate
# lines of text code = 		18 (.cpp) + 9694 (.h) = 9712
# object/library files = 	uvision.../ARM: 5 .o (object) files; 2 .ar (static library???) files
							gcc_arm.../GCC_ARM: 4 .o (object files;  2 .a (static library) files
							
different files:			Only uvision has "HelloWorld.uvopt" and "HelloWorld.uvproj". Only gcc_arm has "Makefile".
							gcc_arm has a subdirectory GCC_ARM.uvision/mbed and uvision has one called "ARM". diff 
							reports the following about those subdirectories:
		Only in ../../../../uvision/mbed/LPC1768/ARM: capi.ar
		Binary files ./cmsis_nvic.o and ../../../../uvision/mbed/LPC1768/ARM/cmsis_nvic.o differ
		Binary files ./core_cm3.o and ../../../../uvision/mbed/LPC1768/ARM/core_cm3.o differ
		Only in .: libcapi.a
		Only in .: libmbed.a
		Only in .: LPC1768.ld
		Only in ../../../../uvision/mbed/LPC1768/ARM: LPC1768.sct
		Only in ../../../../uvision/mbed/LPC1768/ARM: mbed.ar
		Binary files ./startup_LPC17xx.o and ../../../../uvision/mbed/LPC1768/ARM/startup_LPC17xx.o differ
		Only in ../../../../uvision/mbed/LPC1768/ARM: sys.o
		Binary files ./system_LPC17xx.o and ../../../../uvision/mbed/LPC1768/ARM/system_LPC17xx.o differ

entry point: 

2.

3.

***************************************************************************************************

4357 Embedded Firmware Essentials
- Program Assignment #2

1. Login to mbed web site, export the "Hello World" program to all of the following targets. 
   How many text files and how many lines of text code in the exported offline code package?  
   How many binary (library or object) files? 
   How many files are different between (a) and (b)? (Use linux commands: find, wc, diff) (10 points)
   What is the "Entry point address:" of your program?  (hint: using readelf)
   
   a.	Exporting to uVision 
   b.	Exporting to GCC ARM Embedded 

   Note: Right Click your program, then select "export ..."

2. binwalk, objdump, nm to Analysis binaries files
   http://binwalk.org/

3. Optional: git clone https://github.com/mbedmicro/mbed