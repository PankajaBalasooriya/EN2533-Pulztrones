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

void doTasks(){
  int VB_POS = 0;
    while (robot.get_task() != STOP) {
        switch (robot.get_task()) {
            case START_SQUARE:
                start_square();
                robot.set_task(BARCODE); 
                break;
            case BARCODE:
                VB_POS = Counting_and_Line_Navigation();
                robot.set_task(MovetoMaze);
                break;
            case MovetoMaze:
                VB_POS = 0;
                execute_MoveToMaze();
                robot.set_task(MAZE);
                break;
            case MAZE:
                execute_maze(VB_POS);
                robot.set_task(STOP);
                break;
            default:
                robot.set_task(STOP);
                break;
        }
    }
}
  

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
  
  delay(5000);
  Buzzer_UniquePattern();
  
  
  robot.init();
  robot.set_task(MovetoMaze);
  //doTasks();  

  
  //moveForward(-100, -100);


  //Todo: implement revese line folloiwng 

  
}


void loop() {
  FollowWhiteLineReverse();

}

