#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "pid.h"

class RobotController {
private:
    // Constants for wheel and encoder properties
    const float WHEEL_DIAMETER = 65.0; // in mm
    const int COUNTS_PER_REVOLUTION = 360; 
    const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;
    const float MM_PER_COUNT = WHEEL_CIRCUMFERENCE / COUNTS_PER_REVOLUTION;
    const int ROBOT_WIDTH = 50; // in mm

    
    int16_t getEncoderError(long targetCounts, long currentCounts);

public:
    RobotController();
    void init();
    void moveForwardEnc(int distance, int speed);
    void moveBackwardEnc(int distance, int speed);
    void turn90Enc(bool clockwise);
    void turn180Enc();

    void followLineWhite(int baseSpeed);
    void followLineBlack(int baseSpeed);
    
    void stop();
};

#endif // CONTROLLER_H