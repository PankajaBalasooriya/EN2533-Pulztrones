#include <Arduino.h>

#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <adafruit_vl53l0x.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>



#include "motors.h"
#include "BluetoothDebug.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "controller.h"
#include "irs.h"
#include "buzzer.h"
#include "robot.h"
#include "I2CMUX.h"



Robot robot;
I2CMUX mux(0x70);
  

void setup() {
  
  initBluetoothDebug();
  initMotorPins();
  initEncoders();
  initIRSensors();
  initBuzzer();
  mux.begin();

  mux.selectChannel(0);


  Buzzer_Toggle(100);
  delay(2000);
 //calibrateIRSensors();
  Buzzer_Toggle(100);
  
  Buzzer_UniquePattern();
  delay(2000);
  
  //FollowWhiteLine_GivenDistance(250);
  
  
  



   //Serial2.print(Counting_and_Line_Navigation());

  //Todo: implement turning logic
  // add code to move forward untill a junction
  // implement code  to detect presense or absence of a line or a junction

  
}


void loop() {


}

