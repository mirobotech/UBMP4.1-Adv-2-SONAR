/*==============================================================================
 Project: Adv-1-SONAR
 Date:    April 12, 2022
 
 This program implements an ultrasonic SONAR function for HC-SR04 modules.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions
#include    "Sonar.h"           // Include UBMP4 SONAR definitions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program variable definitions
unsigned char range = 0;        // SONAR target range

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
    // Configure TRISC for TRIG output on H1 and ECHO input on H2
    TRISC = 0b00001110;         // Set H1 as output, H2 as SONAR input
	
    while(1)
	{
        if(sonar_ready())
        {
            range = sonar_range_cm();
        }
        
        if(range > 50)
        {
            LATC = 0b11110000;
        } 
        else if(range > 20)
        {
            LATC = 0b01110000;
        }
        else if(range > 10)
        {
            LATC = 0b00110000;
        }
        else if(range > 5)
        {
            LATC = 0b00010000;
        }
        else
        {
            LATC = 0;
        }
        
        // Delay between SONAR pings
        __delay_ms(25);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Learn More - Program Analysis Activities
 * 
 * 1. 
 */