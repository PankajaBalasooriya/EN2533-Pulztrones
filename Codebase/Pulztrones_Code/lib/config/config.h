#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>



// Wheel Dimensions
const float WHEEL_DIAMETER_MM = 66.0;        // mm
const float WHEEL_BASE_MM = 193.0;           // Distance between wheel centers in millimeters
const float ROBOT_RADIUS = WHEEL_BASE_MM / 2.0;

// Constants
const float RADIANS_PER_DEGREE = 2 * PI / 360.0;
const float DEGREES_PER_RADIAN = 360.0 / 2 * PI;
const float DEG_PER_MM_DIFFERENCE = (180.0 / (WHEEL_BASE_MM * PI));


// Encoder Specifications
const float COUNTS_PER_REVOLUTION = 824.0;   // Encoder counts per complete wheel revolution
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;

//constats for the motion control
//Todo: implement rotation bias
// The robot is likely to have wheels of different diameters or motors of slightly
// different characteristics and that must be compensated for if the robot is to
// reliably drive in a straight line.
// This number adjusts the encoder count and must be  added to the right
// and subtracted from the left motor.
//const float ROTATION_BIAS = 0.0025;  // Negative makes robot curve to left
//const float MM_PER_COUNT_LEFT = (1 - ROTATION_BIAS) * MM_PER_COUNT;
//const float MM_PER_COUNT_RIGHT = (1 + ROTATION_BIAS) * MM_PER_COUNT;
const float MM_PER_COUNT_LEFT =  MM_PER_COUNT;
const float MM_PER_COUNT_RIGHT = MM_PER_COUNT;






// Motor and Movement Parameters
const int MAX_PWM_SPEED = 255;         // Maximum PWM speed setting
const int MIN_PWM_SPEED = 50;          // Minimum PWM speed setting

const int BASE_SPEED = 80;
const int MAX_SPEED = 120;
const int MIN_SPEED = 50;

const float SPEEDMAX_EXPLORE = 100; // Maximum speed for scaling


// Control loop timing. Pre-calculate to save time in interrupts
const float LOOP_FREQUENCY = 500.0;
const float LOOP_INTERVAL = (1.0 / LOOP_FREQUENCY);




// hardware configuration

//**** IO CONFIGURATION ****************************************************//
#define ENCODER_LEFT_CLK 19  // Maps to PIND, bit 2
#define ENCODER_RIGHT_CLK 18 // Maps to PIND, bit 3
#define ENCODER_LEFT_B 27    // Maps to PINA, bit 5
#define ENCODER_RIGHT_B 26   // Maps to PINA, bit 4







//*** MOTION CONTROL CONSTANTS **********************************************//

// forward motion controller constants
const float FWD_KP = 0.5;
const float FWD_KD = LOOP_FREQUENCY * 0;

// rotation motion controller constants
const float ROT_KP = 0.5;
const float ROT_KD = LOOP_FREQUENCY * 0;

// controller constants for the steering controller
const float STEERING_KP = 0.04;
const float STEERING_KD = 0.00;
const float STEERING_ADJUST_LIMIT = 10.0;  // deg/s

// encoder polarity is either 1 or -1 and is used to account for reversal of the encoder phases
#define ENCODER_LEFT_POLARITY (-1)
#define ENCODER_RIGHT_POLARITY (1)



//***************************************************************************//

//***** PERFORMANCE CONSTANTS************************************************//
// speeds in mm/s and mm

const int OMEGA_SPIN_TURN = 360;
const int ALPHA_SPIN_TURN = 3600;




/******************************************************************************
 * FAST IO for ATMEGA2560 ONLY
 *
 * There are places in the code (ADC and ENCODERS) where it is important that
 * you are able to access IO pins as quickly as possible. Some processor are fast
 * enough that this is not a problem. The ATMEGA2560 using the Arduino framework
 * is not one of those cases so the macros below translate simple pin IO
 * functions into single machine code instructions.
 *
 * Extracted from digitalWriteFast:
 *      Optimized digital functions for AVR microcontrollers
 *      by Watterott electronic (www.watterott.com)
 *      based on https://code.google.com/p/digitalwritefast
 *
 * If you are using a different processor, you will either need to reimplement
 * these functions or use a suitable built-in function if it is fast enough
 */
// Fast read macros for each encoder pin
/*
#define fast_read_Encoder_LEFT_B() ((int)((PINA & (1UL << 5)) ? HIGH : LOW))
#define fast_read_Encoder_RIGHT_B() ((int)((PINA & (1UL << 4)) ? HIGH : LOW))
#define fast_read_Encoder_LEFT_CLK() ((int)((PIND & (1UL << 2)) ? HIGH : LOW))
#define fast_read_Encoder_RIGHT_CLK() ((int)((PIND & (1UL << 3)) ? HIGH : LOW))
*/






/******************************************************************************
 * ATOMIC OPERATIONS for ATMEGA2560 ONLY
 * Since the ATMega2560 is an 8 bit processor it is possible that you will end
 * up trying to read a multi-byte quantity that is modified in an interrupt while
 * you are doing the read or write. The result is a corrupt value. 32 bit processors
 * are unlikely to suffer from this since quantities are read in a single operation.
 *
 * The AVR compiler provides a method for you to disable interrupts for the
 * duration of a block of code and then restore the state at the end of the block.
 *
 * It is not enough to simply turn off interrupts and then turn them back on because
 * you need to remember the state of the interrupt enable flag at the start of the
 * block.
 *
 * These macros do this for you and should be either modified for different processors
 * or bypassed if needed.
 *
 * Use like this:
 * ATOMIC {
 * // code to protect
 * }
 *
 */
#if defined(__AVR__)
#include <util/atomic.h>
#define ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define ATOMIC
#endif



#endif // CONFIG_H
