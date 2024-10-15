#ifndef PID_H
#define PID_H

// Function to calculate the PID control output for different tasks
int calcPID_WL(int error);   // White Line PID
int calcPID_BL(int error);   // Black Line PID
int calcPID_Enc(int error);  // Encoder-based PID

// Declare global PID variables (if needed)
extern float lastErrWL;
extern float lastErrBL;
extern float lastErrEnc;

#endif
