#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Control loop timing. Pre-calculate to save time in interrupts
const float LOOP_FREQUENCY = 50.0; //Hz
const float LOOP_INTERVAL = (1.0 / LOOP_FREQUENCY);

//***** ROBOT SPECIFICATIONS *****************************************************//
const float WHEEL_DIAMETER_MM = 66.0;
const float WHEEL_BASE_MM = 193.0;
const float ROBOT_RADIUS = WHEEL_BASE_MM / 2.0;

const float COUNTS_PER_REVOLUTION = 824.0;
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;

const float DEG_PER_MM_DIFFERENCE = (180.0 / (WHEEL_BASE_MM * PI));
const float RADIANS_PER_DEGREE = 2 * PI / 360.0;
const float DEGREES_PER_RADIAN = 360.0 / 2 * PI;



//***** IO PINS *****************************************************//
#define ENCODER_LEFT_CLK 19  // Maps to PIND, bit 2
#define ENCODER_RIGHT_CLK 18 // Maps to PIND, bit 3
#define ENCODER_LEFT_B 27    // Maps to PINA, bit 5
#define ENCODER_RIGHT_B 26   // Maps to PINA, bit 4




//*** MOTION CONTROL CONSTANTS **********************************************//
// forward motion controller constants
const float FWD_KP = 0.5;
const float FWD_KD = LOOP_FREQUENCY * 0.5;

// rotation motion controller constants
const float ROT_KP = 0.5;
const float ROT_KD = LOOP_FREQUENCY * 0.5;

// controller constants for the steering controller
const float STEERING_KP = 0.04;
const float STEERING_KD = 0.00;
const float STEERING_ADJUST_LIMIT = 10.0;  // deg/s



// encoder polarity is either 1 or -1 and is used to account for reversal of the encoder phases
#define ENCODER_LEFT_POLARITY (1)
#define ENCODER_RIGHT_POLARITY (1)

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



//***** PERFORMANCE CONSTANTS************************************************//
// search and run speeds in mm/s and mm
const int MAX_SPEED_LINE_FOLLOW = 150;

const int OMEGA_SPIN_TURN = 360;
const int ALPHA_SPIN_TURN = 3600;


/******************************************************************************
 * ATOMIC OPERATIONS for ATMEGA328 ONLY
 * Since the ATMega328 is an 8 bit processor it is possible that you will end
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
//***************************************************************************//

#endif
