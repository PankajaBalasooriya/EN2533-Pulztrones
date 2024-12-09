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
#include"MenuSystem.h"



Robot robot;
I2CMUX mux(0x70);
MenuSystem menu(128, 64, -1, 0x3C);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

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

  mux.selectChannel(4);
// channel 2 -bottom
// channel 3 - middle
// channel 4 - top

  Buzzer_Toggle(100);
  delay(2000);
  //calibrateIRSensors();
  Buzzer_Toggle(100);
  
 // delay(5000);
  //Buzzer_UniquePattern();
  
  
  robot.init();
  //robot.set_task(MovetoMaze);
  //doTasks();  

  
  //moveForward(-100, -100);


  //Todo: implement revese line folloiwng 
    //MoveReverseUntillJunction();
     //MenuSelection 

    //menu.begin();

    Serial2.println("Adafruit VL53L0X test.");
    if (!lox.begin()) {
        Serial2.println(F("Failed to boot VL53L0X"));
        while(1);
    }
    // power
    Serial2.println(F("VL53L0X API Continuous Ranging example\n\n"));

    // start continuous ranging
    lox.startRangeContinuous();

}


void loop() {
  //FollowWhiteLineReverse();
  //mux.selectChannel(0); // channel 0 is selected for OLED
  //menu.handleInput(BUTTON_UP, BUTTON_BACK, BUTTON_SELECT);//MenuSelectioninitiated 
    if (lox.isRangeComplete()) {
    Serial2.print("Distance in mm: ");
    Serial2.println(lox.readRange());
  }

}

