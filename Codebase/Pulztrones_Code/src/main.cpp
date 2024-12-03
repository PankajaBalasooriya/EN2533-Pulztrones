#include <Arduino.h>

#include <QTRSensors.h>

#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"
#include "encoders.h"
#include "controller.h"
#include "irs.h"
#include "buzzer.h"

#include "systick.h"
#include "config.h"
#include "profile.h"
#include "motion.h"
#include "robot.h"
#include "sensors.h"

Encoders encoders;
Motion motion;


Profile forward;
Profile rotation;
Controller controller;

Robot robot;




void setup() {
  
  initBluetoothDebug();
  initMotorPins();

  initIRSensors();
  initBuzzer();
  
  encoders.begin();
  
  
  Buzzer_Toggle(100);
  delay(2000);
  calibrateIRSensors();
  Buzzer_Toggle(100);

  
  delay(5000);
  Buzzer_UniquePattern();
  delay(2000);
  

  Systick_begin();
  
  robot.run(1000);


   
   

  

  
}


void loop() {
  
  


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