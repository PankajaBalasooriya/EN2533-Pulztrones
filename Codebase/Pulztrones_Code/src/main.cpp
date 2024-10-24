#include <Arduino.h>

#include <Adafruit_VL53L0X.h>
#include <QTRSensors.h>

#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "controller.h"



RobotController robot;


// Class instances
QTRSensors qtr;


// initializing the global variables
const uint16_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
bool LineFollowing = false;


float lastError = 0;

// Motor Base speeds
int M1 = 30;
int M2 = 30;


// put function declarations here:
void calibrateIRSensors();
void leftEdgeISR();
void rightEdgeISR();


enum Task {
  START,
  BINARY_CODE_DETECTION,
  LINE_FOLLOWING,
  MAZE_NAVIGATION,
  COLOR_LINE_FOLLOWING,
  COIN_DROP
};

Task currentTask = START;

void setup() {
  
  initBluetoothDebug();
  robot.init();

  //IR Sensor Interrupt pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(2), leftEdgeISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rightEdgeISR, CHANGE);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);

 
  
  //calibrateIRSensors();



 

  
}

void loop() {
// Get and print raw values
/*
switch (currentTask) {
    case START:
        robot.moveForwardEnc(100, 100);
        currentTask = BINARY_CODE_DETECTION;
        break;
}
  */
}

// put function definitions here:

void calibrateIRSensors() {
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  //qtr.setEmitterPin(22); // emitter is controlled by digital pin 22


  for (uint8_t i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);
  }
} 

void leftEdgeISR() {
    if(!LineFollowing){
        return;
    }
}    
    
   

void rightEdgeISR() {
   if(!LineFollowing){
        return;
    }
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

  
*/