#include <Arduino.h>
#include <BluetoothDebug.h>
#include <Adafruit_VL53L0X.h>
#include <QTRSensors.h>

// Define motor control pins
const int rightMotorBackward = 22;
const int rightMotorForward = 23;
const int leftMotorBackward = 24;
const int leftMotorForward = 25;

const int enaPin = 4; // Left
const int enbPin = 3; // Right


// Class instances
QTRSensors qtr;


// initializing the global variables
const uint16_t SensorCount = 8;
uint16_t sensorValues[SensorCount];


float lastError = 0;



// PID control variables
float KP = 1.2; // Proportional gain
//float KI = 0.0; // Integral gain
float KD = 0.8; // Derivative gain

// Motor Base speeds
int16_t M1 = 100;
int16_t M2 = 100;


// put function declarations here:
void moveForward(int16_t, int16_t);
void calibrateIRSensors();

void setup() {
  // put your setup code here, to run once:
  initBluetoothDebug();

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);

  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(enaPin, OUTPUT);
  pinMode(enbPin, OUTPUT);


   calibrateIRSensors();
  
}

void loop() {
  int16_t position = qtr.readLineWhite(sensorValues);

  int16_t error = position - 3500;

  int16_t motorSpeed = KP * error + KD * (error - lastError);
  lastError = error;

  int16_t m1Speed = M1 + motorSpeed;
  int16_t m2Speed = M2 - motorSpeed;


  // Ensure the motor speeds are within valid range
  m1Speed = constrain(m1Speed, 0, 255);
  m2Speed = constrain(m2Speed, 0, 255);

  moveForward(m1Speed, m2Speed);

  

  

}

// put function definitions here:
void moveForward(int16_t SpeedM1, int16_t SpeedM2) {

  analogWrite(enaPin, SpeedM1);
  analogWrite(enbPin, SpeedM2);

  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

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