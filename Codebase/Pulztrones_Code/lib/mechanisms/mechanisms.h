#ifndef MECHANISMS_H
#define MECHANISMS_H

#include <Arduino.h>
#include <Servo.h>

// Pin definitions
const int COIN_DROPPER_PIN = 8;
const int ARM_VERTICAL_PIN = 7;
const int ARM_GRIPPER_PIN = 6;

// Servo position definitions
// Coin Dropper Positions
const int COIN_DROPPER_REST = 180;
const int COIN_DROPPER_ACTIVE = 150;

// Vertical Arm Positions
const int ARM_VERTICAL_LOWEST = 75;
const int ARM_VERTICAL_MIDDLE = 90;
const int ARM_VERTICAL_HIGHEST = 111;

// Gripper Positions
const int GRIPPER_OPEN = 0;
const int GRIPPER_CLOSED = 97;
const int GRIPPER_HOLD = 100;

// Servo movement speed control
const int SERVO_SPEED_SLOW = 1;
const int SERVO_SPEED_MEDIUM = 3;
const int SERVO_SPEED_FAST = 5;




#endif // MECHANISMS_H