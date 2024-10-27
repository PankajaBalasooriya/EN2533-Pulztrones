#include "controller.h"
#include "motors.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "irs.h"

// Constants for robot physical properties
const float WHEEL_DIAMETER_MM = 68.0;
const float WHEEL_BASE_MM = 193.0;
const float COUNTS_PER_REVOLUTION = 826.0;
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;

const int BASE_SPEED = 75;
const int MAX_SPEED = 200;
const int MIN_SPEED = 50;



void FollowBlackLine() {
    // Read the position of the line (0 to 7000)
    int position = readBlackLinePosition();

    // Calculate the error from the center
    int error = position - 3500;

    // Calculate the PID correction value
    float pidOutput = PIDLine(error);
    Serial2.println(pidOutput);

    // Calculate motor speeds
    int leftSpeed = BASE_SPEED + pidOutput;
    int rightSpeed = BASE_SPEED - pidOutput;

    // Constrain motor speeds to the valid range
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);

    // Apply speeds to motors
    moveForward(leftSpeed, rightSpeed);
}

void FollowWhiteLine() {
    // Read the position of the line (0 to 7000)
    int position = readWhiteLinePosition();

    // Calculate the error from the center
    int error = position - 3500;

    // Calculate the PID correction value
    float pidOutput = PIDLine(error);
    Serial2.println(pidOutput);

    // Calculate motor speeds
    int leftSpeed = BASE_SPEED + pidOutput;
    int rightSpeed = BASE_SPEED - pidOutput;

    // Constrain motor speeds to the valid range
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);

    // Apply speeds to motors
    moveForward(leftSpeed, rightSpeed);
}


float Kp_enc = 0, Kd_enc = .000;
float error_enc = 0.0;
float derivative_enc = 0.0, correction_enc = 0.0;

void MoveDistanceForward(float distance){
    const int target_encoder_count = distance / MM_PER_COUNT;
    int encoder_count_left = 0;
    int encoder_count_right = 0;


    resetEncoders();

    while(encoder_count_left < target_encoder_count && encoder_count_left < target_encoder_count){
        encoder_count_left = getLeftEncoderCounts();
        encoder_count_right = getRightEncoderCounts();

        // Calculate encoder-based PID
        error_enc = encoder_count_right - encoder_count_left;
        correction_enc = PIDEnc(error_enc);

        // Combine encoder and IR corrections (with priority on encoder)
        float total_correction = correction_enc;

        // Calculate motor speeds
        float left_speed = BASE_SPEED + total_correction;
        float right_speed = BASE_SPEED - total_correction;

        setMotorLPWM(left_speed);
        setMotorRPWM(right_speed);

    }
    MotorBreak();
    setMotorLPWM(0);
    setMotorRPWM(0);
}
