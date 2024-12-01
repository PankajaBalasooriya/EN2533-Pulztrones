#include "robot.h"

Robot::Robot() {
    // Initialize the robot
    init();
}

void Robot::init(){
    initMotors();
    initEncoders();
    initIRSensors();
    initBuzzer();
}