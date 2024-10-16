// GPT generated: need to change the class and improve accordingly 
/*

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "pid.h"

class RobotController {
private:
    // Constants for wheel and encoder properties
    const float WHEEL_DIAMETER = 65.0; // in mm, adjust to your wheel size
    const int COUNTS_PER_REVOLUTION = 360; // adjust based on your encoder
    const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;
    const float MM_PER_COUNT = WHEEL_CIRCUMFERENCE / COUNTS_PER_REVOLUTION;
    const int ROBOT_WIDTH = 150; // in mm, adjust to your robot's width

    void moveWithPID(long targetCounts, int baseSpeed);
    void turnWithPID(long targetCounts, int baseSpeed, bool clockwise);
    int16_t getEncoderError(long targetCounts, long currentCounts);

public:
    RobotController();
    void init();
    void moveForward(int distance, int speed);
    void moveBackward(int distance, int speed);
    void turn90Degrees(bool clockwise);
    void turn180Degrees();
    void followLineWhite(int baseSpeed);
    void followLineBlack(int baseSpeed);
    void stop();
};

#endif // CONTROLLER_H

*/