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

// Constants for robot physical properties
const float WHEEL_DIAMETER_MM = 68.0;
const float WHEEL_BASE_MM = 193.0;
const float COUNTS_PER_REVOLUTION = 826.0;
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;


// Constants for line following
const int BASE_SPEED = 75;  
const int MAX_SPEED = 200;   
const int MIN_SPEED = 50;     



/* Without dt
const float KP = 0.035;        // Proportional gain
const float KD = 0.250;       // Derivative gain
0.0148
0.0005
*/

const float KP = 0.0152;        // Proportional gain
const float KD = 0.00075;       // Derivative gain

// Variables for PID calculation
float lastError = 0;

unsigned long prevTimePID = 0;

// Function to calculate PID output
float calculatePID(int error) {
    unsigned long currentTimePID = millis();
    float dt = (currentTimePID - prevTimePID) / 1000.0;
    prevTimePID = currentTimePID;
    // Proportional term
    float P = error * KP;
    
    // Derivative term
    float D = ((error - lastError) / dt) * KD;
    lastError = error;
    
    
    // Calculate total correction
    return P + D;
}

void lineFollowingLoop() {
    // Read the position of the line (0 to 7000)
    // For 8 sensors, the value will be between 0 and 7000
    // 3500 represents the center position
    int position = readBlackLinePosition();
    
    
    // Calculate the error from center
    // Error will be positive when line is on the right, negative when on the left
    int error = position - 3500;

    
    
    // Calculate the PID correction value
    float pidOutput = calculatePID(error);
    Serial2.println(pidOutput);
    // Calculate motor speeds
    int leftSpeed = BASE_SPEED + pidOutput;
    int rightSpeed = BASE_SPEED - pidOutput;
    
    // Constrain motor speeds to valid range
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
    
    // Apply speeds to motors
    moveForward(leftSpeed, rightSpeed);
}

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






void setup() {
  
  initBluetoothDebug();
  initMotorPins();
  initEncoders();
  initIRSensors();

  Timer1.initialize(20000); // at 20 ms
  Timer1.attachInterrupt(updateVelocities);
  
  
  delay(2000);
  calibrateIRSensors();


   
   

  

  
}
int k = 1;

void loop() {
  
  
  
  lineFollowingLoop();


}


































// line following loop
/*
int16_t position = qtr.readLineWhite(sensorValues);

  int error = position - 3500;


  int motorSpeed = calcPID_WL(error);
  

  int16_t m1Speed = M1 + motorSpeed;
  int16_t m2Speed = M2 - motorSpeed;


  // Ensure the motor speeds are within valid range
  m1Speed = constrain(m1Speed, 0, 255);
  m2Speed = constrain(m2Speed, 0, 255);

  moveForward(m1Speed, m2Speed);
  




// encoder loop
static unsigned long lastPrintTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastPrintTime >= 100) {  
        Serial2.print("Left Encoder: ");
        Serial2.print(getLeftEncoderCounts());
        Serial2.print(", Right Encoder: ");
        Serial2.println(getRightEncoderCounts());
        lastPrintTime = currentTime;
    }

  




  //printing 
  qtr

  // Read QTR sensor values and get the line position
    int16_t position = qtr.readLineWhite(sensorValues);

    // Print QTR sensor values to Serial2
    //Serial2.print("QTR Sensor Values: ");
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial2.print(sensorValues[i]);
        if (i < SensorCount - 1) {
            Serial2.print(", ");
        }
    }
    Serial2.println();

    // Add a delay to avoid printing too fast
    delay(100);
*/