#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Wheel Dimensions
const float WHEEL_DIAMETER_MM = 66.0;        // mm
const float WHEEL_BASE_MM = 193.0;           // Distance between wheel centers in millimeters

// Encoder Specifications
const float COUNTS_PER_REVOLUTION = 824.0;   // Encoder counts per complete wheel revolution
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;




// Motor and Movement Parameters
const int MAX_PWM_SPEED = 255;         // Maximum PWM speed setting
const int MIN_PWM_SPEED = 50;          // Minimum PWM speed setting


// Control loop timing. Pre-calculate to save time in interrupts
const float LOOP_FREQUENCY = 500.0;
const float LOOP_INTERVAL = (1.0 / LOOP_FREQUENCY);



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



#endif // CONFIG_H
