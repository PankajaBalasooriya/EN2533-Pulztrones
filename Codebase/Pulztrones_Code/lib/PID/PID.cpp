#include "PID.h"
#include "Arduino.h"
#include "motors.h"
#include "encoders.h"



// PID constants
const float KpL = 0.062;//0.04
const float KdL = 7;

const float KpEnc = 1;
const float KdEnc = 0;

// Static variables for PID calculation
static float lastError = 0;
//static unsigned long prevTimePID = 0;


float PIDLine(int error) {
    
    // Proportional term
    float P = error * KpL;
    
    // Derivative term
    float D = (error - lastError) * KdL;
    lastError = error;
    
    // Calculate total correction
    return P + D;
}

float PIDEnc(int error) {
    
    // Proportional term
    float P = error * KpEnc;
    
    // Derivative term
    float D = (error - lastError) * KdEnc;
    lastError = error;
    
    // Calculate total correction
    return P + D;
}

