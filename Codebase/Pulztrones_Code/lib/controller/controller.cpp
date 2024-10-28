#include "controller.h"
#include "motors.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "irs.h"

// Constants for robot physical properties
const float WHEEL_DIAMETER_MM = 68.0;
const float WHEEL_BASE_MM = 193.0;
const float COUNTS_PER_REVOLUTION = 824.0;
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;

const int BASE_SPEED = 90;
const int MAX_SPEED = 200;
const int MIN_SPEED = 50;



void FollowBlackLine() {
    // Read the position of the line (0 to 7000)
    int position = readBlackLinePosition();

    // Calculate the error from the center
    int error = position - 3500;

    

    // Calculate the PID correction value
    float pidOutput = PIDLine(error);
    //Serial2.println(pidOutput);

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
    
    // Check for junction
    /*
    if (isAtTJunction() || isAtLJunction()) {
        // Stop the robot
        //moveForward(0, 0);
        //delay(500);  // Short pause to ensure complete stop
        MoveDistanceForward(50);  // Move forward slightly to clear the junction

        MotorBreak();

        
        // Handle the junction (modify direction as needed)
        handleJunction('L');  // Default to left turn
        return;
    }
    */
   int leftIR = analogRead(A8);
   int rightIR = analogRead(A9);
   bool j = isAtJunction(leftIR, rightIR);
   bool L = isAtLJunction(j, leftIR, rightIR);
   bool T = isAtTJunction(j, leftIR, rightIR);
   

   if (T || L) {
        // Stop the robot
        MoveDistanceForward(40);
        MotorBreak();
        
    
        if (T) {
            handleJunction('S');
        } else if (L) {
            if (leftSide) {
                handleJunction('L');
            } else {
                handleJunction('R');
            }
        }
        return;
    }





    // Normal line following code continues...
    int error = position - 3500;
    float pidOutput = PIDLine(error);
    
    int leftSpeed = BASE_SPEED + pidOutput;
    int rightSpeed = BASE_SPEED - pidOutput;
    
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
    
    moveForward(leftSpeed - 20, rightSpeed);
}








float error_enc = 0.0;
float correction_enc = 0.0;

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

void turn(int direction) {


    // Constants
    const int COUNTS_PER_90_DEGREE = 1080; // Experimentally determined
    const float MAX_TURN_SPEED = 100; // Maximum turn speed
    const float MIN_TURN_SPEED = 70; // Minimum turn speed to overcome static friction

    // PD controller constants
    const float Kp = 0.7; // Proportional gain
    const float Kd = 0.1; // Derivative gain

    // Variables
    int target_encoder_diff = COUNTS_PER_90_DEGREE;
    int encoder_diff = 0;
    int left_encoder_current, right_encoder_current;
    float error = 0, last_error = 0, derivative = 0;
    float turn_speed = 0;

    // Reset encoders
    resetEncoders();

    while (encoder_diff < target_encoder_diff) {
        // Get current encoder counts
        left_encoder_current = getLeftEncoderCounts();
        right_encoder_current = getRightEncoderCounts();

        // Calculate encoder difference
        encoder_diff = abs(right_encoder_current - left_encoder_current);

        // Calculate error
        error = target_encoder_diff - encoder_diff;

        // Calculate derivative
        derivative = error - last_error;

        // PD controller
        turn_speed = Kp * error + Kd * derivative;

        // Limit turn speed
        turn_speed = fmin(fmax(turn_speed, MIN_TURN_SPEED), MAX_TURN_SPEED);

        // Set motor speeds based on direction
        float left_speed = (direction > 0) ? turn_speed : -turn_speed;
        float right_speed = (direction > 0) ? -turn_speed : turn_speed;

        // Apply motor speeds
        setMotorLPWM(left_speed);
        setMotorRPWM(right_speed);

        // Save current error for next iteration
        last_error = error;

        // Small delay to avoid overwhelming the microcontroller
    }

    // Stop motors after reaching the target
    setMotorLPWM(0);
    setMotorRPWM(0);

    // Reset encoders
    resetEncoders();
}


void handleJunction(char direction) {
    // Stop briefly
    MotorBreak();
    
    if (direction == 'L') {
        turn(-1);  // Turn left
    } else if (direction == 'R') {
        turn(1);  // Turn right
    } else if (direction == 'S') {
        MoveDistanceForward(0);
    }
}


