#include "pid.h"
#include <Arduino.h>

// PID control variables for white line following
float KpWL = 1.0;
float KdWL = 0.22;
float lastErrWL = 0;

// PID control variables for black line following
float KpBL = 1.0;
float KdBL = 0.7;
float lastErrBL = 0;

// PID control variables for movement using encoders
float KpEnc = 1.5;
float KdEnc = 0.9;
float lastErrEnc = 0;

// PID function for white line following
int calcPID_WL(int error) {
    int motorSpeed = KpWL * error + KdWL * (error - lastErrWL);
    lastErrWL = error;
    return motorSpeed;
}

// PID function for black line following
int calcPID_BL(int error) {
    int motorSpeed = KpBL * error + KdBL * (error - lastErrBL);
    lastErrBL = error;
    return motorSpeed;
}

// PID function for movement using encoders
int calcPID_Enc(int16_t error) {
    int motorSpeed = KpEnc * error + KdEnc * (error - lastErrEnc);
    lastErrEnc = error;
    return motorSpeed;
}
