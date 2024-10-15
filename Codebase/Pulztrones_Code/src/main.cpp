#include <Arduino.h>

#include <Adafruit_VL53L0X.h>
#include <QTRSensors.h>

#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"



// Class instances
QTRSensors qtr;


// initializing the global variables
const uint16_t SensorCount = 8;
uint16_t sensorValues[SensorCount];


float lastError = 0;





// Motor Base speeds
int M1 = 30;
int M2 = 30;


// put function declarations here:
void calibrateIRSensors();

void setup() {
  
  initBluetoothDebug();
  initMotorPins();
  Serial2.begin(9600);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);

  
   calibrateIRSensors();
  
}

void loop() {
  int16_t position = qtr.readLineWhite(sensorValues);

  int error = position - 3500;
  Serial2.print(error);
  Serial2.print(",");

  int motorSpeed = calcPID_WL(error);
  

  int16_t m1Speed = M1 + motorSpeed;
  int16_t m2Speed = M2 - motorSpeed;


  // Ensure the motor speeds are within valid range
  m1Speed = constrain(m1Speed, 0, 255);
  m2Speed = constrain(m2Speed, 0, 255);

  moveForward(m1Speed, m2Speed);
  

  

  

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