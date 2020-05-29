/* © Ahmad Siraj MY
 *
 * Created:   Thu May 28 2020
 * Processor: PIC18F4580
 * Compiler:  MPLAB C18
 */

#include <p18f4580.h>
#include <delays.h>
#define s1 PORTDbits.RD0
#define s2 PORTDbits.RD1
#define s3 PORTDbits.RD2
#define s4 PORTDbits.RD3
#define gled PORTCbits.RC1
#define rled PORTCbits.RC0
#define oled PORTCbits.RC2
void detect();
void open();
void close();
void operat();

void main(void)
 { 
   int stat = 1; 
   TRISC = 0; //port C all as output
   TRISD = 1; //port D all as input for digital I/O1
    
    while(s1 == 0);
    while(1) {
        switch (s1)
        {
        case 1:     
                    if (stat == 0)
                    {
                    if (s4 == 1) {
                        gled = 0;
                        rled = 0;
                        detect();
                    }
                        gled = 0;
                        rled = 1;
                        close();
                        if (s2 == 1) {
                            while (s1 == 1);
                            stat = 1;
                        }
                    } else if (stat == 1) {
                    if (s4 == 1) {
                        gled = 0;
                        rled = 0;
                        detect();
                    }
                        rled = 0;
                        gled = 1;
                        open();
                        if (s3 ==1) {
                            while (s1 == 1);
                            stat = 0;
                        }
                    }
            break;
        default:
        oled = 0;
        rled = 0;
        gled = 0;
            break;
        }
    }
}

void detect() {
    while (s4 == 1) {
    oled = 1;
    gled = 0;
    rled = 0;
    }
    oled = 0;
}

void open() {
    while (s4 == 0) {
        Delay10KTCYx(1);
        gled = 1;
        Delay10KTCYx(1);
        gled = 0;
       if (s1 == 0) {
	  break;
       } else if (s3 == 1) {
	  gled = 1;
	  break;
       }
    }
}

void close() {
    while (s4 == 0) {
        Delay10KTCYx(1);
        rled = 1;
        Delay10KTCYx(1);
        rled = 0;
       if (s1 == 0) {
	  break;
       } else if (s2 == 1) {
	  rled = 1;
	  break;
       }
    }
}
