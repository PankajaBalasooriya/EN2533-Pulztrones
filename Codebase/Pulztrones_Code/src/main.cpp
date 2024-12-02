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
#include "irs.h"
#include "buzzer.h"
#include "config.h"

#include "robot.h"
#include "systick.h"
#include "motion.h"

Systick sysTick;
Encoders encoders;
Motion motion;
Controller controller;
Profile forward;
Profile rotation;
Robot robot;

ISR(TIMER2_COMPA_vect, ISR_NOBLOCK) {
  systick.update();
}


void setup() {
  
  initBluetoothDebug();
  initMotors();
  //initEncoders();
  initIRSensors();
  //initBuzzer();

  //controller.begin();
    encoders.begin();
  

  
  
  //Buzzer_Toggle(100);
  delay(2000);
  calibrateIRSensors();
  //Buzzer_Toggle(100);

  
  delay(5000);
  //Buzzer_UniquePattern();
  delay(2000);
  
  

   sysTick.begin();

  

  
}


void loop() {
  


}





















