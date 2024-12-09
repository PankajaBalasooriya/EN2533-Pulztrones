#include "ArmMechanism.h"

// Constructor
ArmMechanism::ArmMechanism() {
    // Constructor can be empty as we'll use init() for setup
}

// Initialization method
void ArmMechanism::init(int armLiftServoPin, int gripperServoPin) {
    // Attach servos to their respective pins
    armLiftServo.attach(armLiftServoPin);
    gripperServo.attach(gripperServoPin);

    digitalWrite(ARM_GRIPPER_ON_PIN, HIGH);
    delay(200);

    // Set initial positions
    moveArmLiftServo(ARM_REST_ANGLE);
    moveGripperServo(GRIPPER_OPEN_ANGLE);

    digitalWrite(ARM_GRIPPER_ON_PIN, LOW);
    delay(200);

}

// Servo movement methods with angle constraint
void ArmMechanism::moveArmLiftServo(int angle) {
    int constrainedAngle = constrain(angle, ARM_LIFT_MIN_ANGLE, ARM_LIFT_MAX_ANGLE);
    armLiftServo.write(constrainedAngle);
    delay(MOVEMENT_PAUSE);
}

void ArmMechanism::moveGripperServo(int angle) {
    int constrainedAngle = constrain(angle, GRIPPER_MIN_ANGLE, GRIPPER_MAX_ANGLE);
    gripperServo.write(constrainedAngle);
    delay(MOVEMENT_PAUSE);
}

// Arm positioning methods
void ArmMechanism::moveToPickupPosition() {
    digitalWrite(ARM_GRIPPER_ON_PIN, HIGH);
    delay(200);
    moveArmLiftServo(ARM_PICKUP_ANGLE);
}

void ArmMechanism::moveToRestPosition() {
    digitalWrite(ARM_GRIPPER_ON_PIN, HIGH);
    delay(200);
    moveArmLiftServo(ARM_REST_ANGLE);
    digitalWrite(ARM_GRIPPER_ON_PIN, LOW);
    delay(200);
}

void ArmMechanism::openGripper() {
    digitalWrite(ARM_GRIPPER_ON_PIN, HIGH);
    delay(200);
    moveGripperServo(GRIPPER_OPEN_ANGLE);
    digitalWrite(ARM_GRIPPER_ON_PIN, LOW);
    delay(200);
}

void ArmMechanism::closeGripper() {
    digitalWrite(ARM_GRIPPER_ON_PIN, HIGH);
    delay(200);
    moveGripperServo(GRIPPER_CLOSE_ANGLE);
}


