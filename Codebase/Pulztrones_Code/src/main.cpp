#include <Arduino.h>

#include <QTRSensors.h>
#include "Ticker.h"
#include <MPU6500_WE.h>


#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "controller.h"
#include "data.h"
#include "irs.h"


// Constants for line following
const int BASE_SPEED = 75;  // Base motor speed (0-255)
const int MAX_SPEED = 200;   // Maximum motor speed
const int MIN_SPEED = 40;     // Minimum motor speed

// PID Constants - adjust these values for your robot
const float KP = 0.035;        // Proportional gain
const float KI = 0;      // Integral gain
const float KD = 0.250;       // Derivative gain
//0.055
/*
const float KP = 0.55;        // Proportional gain
const float KI = 0;      // Integral gain
const float KD = 0.35;       // Derivative gain
*/

// Variables for PID calculation
float lastError = 0;
float integral = 0;

// Function to calculate PID output
float calculatePID(int error) {
    // Proportional term
    float P = error * KP;
    
    // Integral term
    integral += error;
    integral = constrain(integral, -10000, 10000);  // Prevent integral windup
    float I = integral * KI;
    
    // Derivative term
    float D = (error - lastError) * KD;
    lastError = error;
    
    // Calculate total correction
    return P + I + D;
}

void lineFollowingLoop() {
    // Read the position of the line (0 to 7000)
    // For 8 sensors, the value will be between 0 and 7000
    // 3500 represents the center position
    int position = readBlackLinePosition();
    
    
    // Calculate the error from center
    // Error will be positive when line is on the right, negative when on the left
    int error = position - 3500;

    //Serial2.print(error);
    //Serial2.print(", ");
    
    // Calculate the PID correction value
    float pidOutput = calculatePID(error);
    
    // Calculate motor speeds
    int leftSpeed = BASE_SPEED + pidOutput;
    int rightSpeed = BASE_SPEED - pidOutput;
    
    // Constrain motor speeds to valid range
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
    
    // Apply speeds to motors
    moveForward(leftSpeed, rightSpeed);
}



void setup() {
  
  initBluetoothDebug();
  initMotorPins();
  initEncoders();
  initIRSensors();
  
  
  delay(2000);
  calibrateIRSensors();

  

   
   

  

  
}

void loop() {
  
  lineFollowingLoop();
    
  

 //printEncoderData();
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