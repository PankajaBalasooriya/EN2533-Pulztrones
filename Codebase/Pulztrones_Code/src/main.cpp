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
#include "tasks.h"



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
  calibrateIRSensors();
  Buzzer_Toggle(100);
  
  Buzzer_UniquePattern();
  delay(2000);
  

  while (robot.get_task() != STOP) {
        switch (robot.get_task()) {
            case START_SQUARE:
                start_square();
                robot.set_task(BARCODE); // Proceed to the next task
                break;
            case BARCODE:
                Counting_and_Line_Navigation();
                robot.set_task(WHITE_LINE_FOLLOW);
                break;
            case WHITE_LINE_FOLLOW:
                execute_white_line_follow();
                robot.set_task(MAZE);
                break;
            case MAZE:
                execute_maze();
                
                break;
            default:
                robot.set_task(STOP);
                break;
        }
    }
  

  
}


void loop() {
  

}

