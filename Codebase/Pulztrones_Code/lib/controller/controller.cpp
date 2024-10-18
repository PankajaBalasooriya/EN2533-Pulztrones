#include <Arduino.h>
#include "controller.h"


RobotController::RobotController() {}

void RobotController::init() {
    initMotorPins();
    initEncoders();
}

int16_t RobotController::getEncoderError(long targetCounts, long currentCounts) {
    return targetCounts - currentCounts;
}

void RobotController::followLineWhite(int baseSpeed) {
    return;
}

void RobotController::moveForwardEnc(int distance, int speed){
    return;
}