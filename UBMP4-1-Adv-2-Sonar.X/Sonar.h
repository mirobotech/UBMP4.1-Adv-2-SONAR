/*==============================================================================
 File: Sonar.h
 Date: April 12, 2022
 
 UBMP4 SONAR function prototypes
 
 Function prototypes and pin definitions for detecting distance using a SONAR
 (HC-SR04 ultrasonic) module on UMBP4 header pins.
==============================================================================*/

// SONAR module header pin definitions ? Modify I/O pin definitions to match the
// UBMP4 header pins your SONAR module is connected to. Ensure TRIG pin is set
// as an output and ECHO pin as an input in the TRISC register.

#define TRIG        LATCbits.LATC0  // SONAR TRIG output pin on H1
#define ECHO        PORTCbits.RC1   // SONAR ECHO input pin on H2

/**
 * Function: bool sonar_ready(void)
 * 
 * Returns the status of a SONAR module. Returns 0 (false) if a previous ECHO
 * pulse is still in progress, or 1 (true) if ECHO is finished and the module
 * is ready to be triggered.
 * 
 * Example usage: while(!sonar_ready());
 * Note: some modules may require a short delay after ECHO finishes and before
 * the next TRIG pulse.
 */
bool sonar_ready(void);

/**
 * Function: unsigned char sonar_range_cm(void)
 * 
 * Returns the distance to the nearest object in cm, or 0 if no object is found.
 * Set the max_range variable to ignore objects beyond the specified maximum
 * range. Since this function can exit while the module is receiving an ECHO,
 * use the sonar_ready() function to ensure the module is ready before ranging.
 * 
 * Example usage: distance = sonar_range_cm();
 */
unsigned char sonar_range_cm(void);
