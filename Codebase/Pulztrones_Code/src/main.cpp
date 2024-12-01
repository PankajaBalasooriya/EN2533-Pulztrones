#include <Arduino.h>

#include <QTRSensors.h>
#include <MPU6500_WE.h>
#include <TimerOne.h>


#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "controller.h"
#include "data.h"
#include "irs.h"
#include "buzzer.h"
#include "config.h"




unsigned long prevTimeCalc = 0;
float leftVel = 0;
float rightVel = 0;
volatile long prevLeftCount = 0, prevRightCount = 0;
volatile float actualVelX = 0, actualVelW = 0;
volatile float encoderVelW = 0;




void updateVelocities() {
    unsigned long currentTime = millis();
    float deltaTime = (currentTime - prevTimeCalc) / 1000.0;
    prevTimeCalc = currentTime;
    
    // Read encoder counts
    long leftCount = getLeftEncoderCounts();
    long rightCount = getRightEncoderCounts();
    
    
    // Calculate wheel velocities in mm/s
     leftVel = ((leftCount - prevLeftCount) * MM_PER_COUNT) / deltaTime;
    rightVel = ((rightCount - prevRightCount) * MM_PER_COUNT) / deltaTime;
    
    prevLeftCount = leftCount;
    prevRightCount = rightCount;
    
    // Calculate linear and angular velocities
    actualVelX = (leftVel + rightVel) / 2.0;
    encoderVelW = (rightVel - leftVel) / WHEEL_BASE_MM;
    
    //gyroVelW = getGyroZ() * DEG_TO_RAD;


    // Apply low-pass filter
    //const float alpha = 0.8; // Filter coefficient (0-1)
    //actualVelW = alpha * gyroVelW + (1 - alpha) * encoderVelW;
    actualVelW = encoderVelW;
}




float steering_KP = 0.04;         // Proportional constant (tune as needed)
float steering_KD = 0;         // Derivative constant (tune as needed)
float last_error = 0.0;          // To store the previous error for derivative calculation
const float SPEEDMAX_EXPLORE = 100.0; // Maximum speed for scaling
const float ADJUST_LIMIT = 60.0; // Limit for adjustment value

unsigned long last_loop_time = 0;  // To store the previous loop time
float LOOP_INTERVAL = 0.01;       // Initialize with a default value (in seconds)

int base_speed = 100;
int MAX_MOTOR_SPEED = 200;
int left_motor_speed = 0;
int right_motor_speed = 0;




float calculate_steering_adjustment(float error) {
    // Calculate the proportional term
    float pTerm = steering_KP * error;

    // Calculate the derivative term
    float dTerm = steering_KD * (error - last_error);
    dTerm = dTerm / LOOP_INTERVAL;

    // Combine proportional and derivative terms
    float adjustment = (pTerm + dTerm);

    // Scale adjustment by forward speed
    adjustment *= (actualVelX) / SPEEDMAX_EXPLORE;

    // Constrain the adjustment to the allowable range
    //adjustment = constrain(adjustment, -ADJUST_LIMIT, ADJUST_LIMIT);

    // Update the last error for the next iteration
    last_error = error;

    // Return the calculated adjustment
    return adjustment;
}

// Variables for the omega controller
float s_omega_error = 0;          // Current omega error
float s_old_omega_error = 0;      // Previous omega error
const float rotKP = 1.0;          // Proportional gain (tune as needed)
const float rotKD = 0.1;          // Derivative gain (tune as needed)
extern bool g_steering_enabled;   // Global flag to enable/disable steering


// rotation controller
float omega_controller(float omega, float steering_adjustment) {
    float omega_error = actualVelW - omega;

    //omega_error += steering_adjustment
    // Add steering adjustment if steering is enabled
    if (g_steering_enabled) {
        omega_error += steering_adjustment;
    }

    // Calculate the derivative term
    float d_term = omega_error - s_old_omega_error;

    // Update the old omega error
    s_old_omega_error = s_omega_error;

    // Calculate the output using proportional and derivative terms
    float output = rotKP * s_omega_error + rotKD * d_term / LOOP_INTERVAL;

    return output;
}




void setup() {
  
  initBluetoothDebug();
  //initMotors();
  //initEncoders();
  //initIRSensors();
  //initBuzzer();
  

  
  
  Buzzer_Toggle(100);
  delay(2000);
  calibrateIRSensors();
  Buzzer_Toggle(100);

  
  delay(5000);
  Buzzer_UniquePattern();
  delay(2000);
  
  
  Timer1.initialize(30000); // at 30 ms
  Timer1.attachInterrupt(updateVelocities);

   

  

  
}


void loop() {
  
//// Read QTR sensor values and get the line position
    //int16_t position = readWhiteLinePosition();
    int16_t position = readBlackLinePosition();
    float error = position - 3500;

    float alpha = 0.1;
    error = alpha * error + (1 - alpha) * error; // expoenential  moving average filter

    float steering_adjustment = calculate_steering_adjustment(error);

    // Calculate motor speeds
    left_motor_speed = base_speed + steering_adjustment;
    right_motor_speed = base_speed - steering_adjustment;

    // Constrain motor speeds to valid PWM range (-255 to 255)
    left_motor_speed = constrain(left_motor_speed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    right_motor_speed = constrain(right_motor_speed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);

    // Set motor speeds
    setMotorLPWM(left_motor_speed);
    setMotorRPWM(right_motor_speed);

    
    // Format and send position data for Serial Plotter
    Serial2.print(">");
    Serial2.print("V:");
    Serial2.print(actualVelX);
    Serial2.print(",W:");
    Serial2.print(actualVelW);
    Serial2.print("\r\n");
    
    //delay(100); // Delay for smoother plotting

  //printEncoderData();

}





















