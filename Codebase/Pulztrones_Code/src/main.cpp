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
#include "CoinDropper.h"
#include "ArmMechanism.h"
#include "Ultrasonic.h"




Robot robot;
I2CMUX mux(0x70);
MenuSystem menu(128, 64, -1, 0x3C);
CoinDropper coinDropper;
ArmMechanism armMechanism;
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);








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
    

    //setting to channel 0 for OLED
    mux.selectChannel(0);


    Buzzer_Toggle(100);
    delay(2000);
    calibrateIRSensors();
    Buzzer_Toggle(100);

    robot.init();
    //coinDropper.init(COIN_DROPPER_SERVO_PIN);
    //armMechanism.init(ARM_LIFT_SERVO_PIN, GRIPPER_SERVO_PIN);

    robot.set_task(MovetoMaze);
    

    //menu.begin();

    //FollowBlackLine();

    //MoveReverseUntillJunction();

    
//      mux.selectChannel(2);
// // channel 2 -bottom
// // channel 3 - middle
// // channel 4 - top
    
    
 
    doTasks();  
    
    // MoveReverseUntillJunction();
    // robot.turn_Left_90_after_moving_reverse();
    // FollowWhiteLineUntilJunction();


    
}


void loop() {
    //FollowWhiteLineReverse();
    // mux.selectChannel(0); // channel 0 is selected for OLED
    // menu.handleInput(BUTTON_UP, BUTTON_DOWN, BUTTON_SELECT);//MenuSelectioninitiated 
    //FollowWhiteLineReverse();
//     Serial2.print(">");
//     Serial2.print("C:");
//     Serial2.print(3500);
//     Serial2.print(",E:");
//    Serial2.println(readBlackLinePosition());
    
    //FollowBlackLine();
}

