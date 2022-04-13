/*==============================================================================
 Library: Sonar
 Date: April 12, 2022
 
 Sonar function for ultrasonic distance ranging using an HC-SR04 SONAR module
 connected to two UBMP4 header pins.
 
 Before using the sonar function, modify the UBMP4_config() function in UBMP4.c
 or add your own PORTC configuration code to configure the TRIG pin as an output
 and the ECHO pin as an input.
 =============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4 constants and functions
#include    "Sonar.h"           // Include UBMP4 SONAR definitions

// Check and return the status of the SONAR module. (Required befor using the
// sonar_range_cm function since it can exit while the module is still waiting
// to receive an ECHO.)

bool sonar_ready(void)
{
	if(ECHO == 1)   			// Check if previous ECHO is finished
        return(0);              // ECHO still in progress - not ready (0 - false)
    return(1);                  // ECHO finished - ready (1 - true)
}

// Return the distance to the nearest object in cm. Set max_range to ignore
// objects beyond the specified range.

unsigned char sonar_range_cm(void)
{
    unsigned char cm = 0;       // Clear cm range counter
    const char max_range = 100; // Set maximum range for objects (must be <= 255)
    
	TRIG = 1;                   // TRIGger a new SONAR ping
	__delay_us(10);
	TRIG = 0;
	while(ECHO == 0);           // Wait for the ping transmission to finish
    
	while(ECHO == 1)            // Determine range by timing received ECHO pulse
	{
		__delay_us(58);			// 2cm speed of sound delay = 1cm distance to
		cm ++;                  // account for ping travel to target and back
		if(cm == max_range)     // Return 0 at max_range before ECHO ends, or...
			return(0);
	}
	return(cm);                 // ...return range at end of ECHO
}
