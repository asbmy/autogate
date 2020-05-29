/* © Ahmad Siraj MY
 *
 * Created:   Thu May 28 2020
 * Processor: PIC18F4580
 * Compiler:  MPLAB C18
 */

#include <p18f4580.h>
#include <delays.h>
#define s1 PORTDbits.RD0 //Switch 1
#define s2 PORTDbits.RD1 //Switch 2
#define s3 PORTDbits.RD2 //Switch 3
#define s4 PORTDbits.RD3 //Sensor
#define gled PORTCbits.RC1 //green LED
#define rled PORTCbits.RC0 //red LED
#define oled PORTCbits.RC2 //Orange LED
void detect();
void open();
void close();

void main(void)
 { 
   int stat = 1; //am using this to remember if the gate has openned or close (this is the gate's memory state)
   TRISC = 0; //port C all as output
   TRISD = 1; //port D all as input for digital I/O1
    
    while(s1 == 0); //awaits the switch 1 turn on first
    while(1) { //infinite loop
        switch (s1) //check if switch is on or off
        {
        case 1:     
                    if (stat == 0) //checks memory state, if the gate was opening or closing (this one is opening)
                    {
                        if (s4 == 1) { //detects collision, if there's any
                            gled = 0;
                            rled = 0;
                            detect(); //detection module
                        }
                            gled = 0;
                            rled = 1;
                            close(); //runs the blinking red led module
                            if (s2 == 1) {
                                while (s1 == 1); //awaits to turn off in order to change gate state
                                stat = 1; //gate is now switch to opening, serves as memory for gate
                            }
                    } else if (stat == 1) { //if gate was opening
                        if (s4 == 1) { //detects collision, if there's any
                            gled = 0;
                            rled = 0;
                            detect(); //detection module
                        }
                            rled = 0;
                            gled = 1;
                            open(); //runs the blinking green led module
                            if (s3 ==1) { 
                                while (s1 == 1); //awaits to turn off in order to change gate state
                                stat = 0; //gate is now switch to closing, serves as memory for gate
                            }
                    }
            break;
        default: //if the switch was off, it will turn everything off
        oled = 0;
        rled = 0;
        gled = 0;
            break;
        }
    }
}

void detect() { //the detection module
    while (s4 == 1) { //while the object is still there, this thing will continue looping
    oled = 1;
    gled = 0;
    rled = 0;
    }
    oled = 0; //turns the orange LED off since there are no obstacles
}

void open() {
    while (s4 == 0) {
        Delay10KTCYx(1); //using the delay function to blink blink
        gled = 1;
        Delay10KTCYx(1);
        gled = 0;
       if (s1 == 0) { //incase switch turns off
	  break;
       } else if (s3 == 1) { //incase the gate has been completely open
	  gled = 1;
	  break; // break is used to force exit a loop
       }
    }
}

void close() {
    while (s4 == 0) {
        Delay10KTCYx(1); //using the delay function to blink blink
        rled = 1;
        Delay10KTCYx(1);
        rled = 0;
       if (s1 == 0) { //incase switch turns off
	  break;
       } else if (s2 == 1) { //incase the gate has been completely closed
	  rled = 1;
	  break;
       }
    }
}
