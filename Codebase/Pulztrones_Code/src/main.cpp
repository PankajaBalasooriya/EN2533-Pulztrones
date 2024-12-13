#include <Arduino.h>

#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <VL53L0X.h>    



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
#include "ToF.h"




Robot robot;
I2CMUX mux(0x70);
MenuSystem menu(128, 64, -1, 0x3C);
CoinDropper coinDropper;
ArmMechanism armMechanism;
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
VL53L0X_Multiplexer tofSensors;








void doTasks(){
  int VB_POS = 0;
  String color = "";
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
                
                execute_MoveToMaze();
                robot.set_task(MAZE);
                break;
            case MAZE:
                VB_POS = 2;
                execute_maze(VB_POS);
                robot.set_task(COLOR_LINE);
                break;
            case COLOR_LINE:
                color = exectute_colorLineFollowing();
                robot.set_task(STOP);
                break;
            case STOP:
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
    tofSensors.begin(mux);

    


    Buzzer_Toggle(100);
    delay(2000);
    calibrateIRSensors();
    Buzzer_Toggle(100);

    delay(5000);
    Buzzer_Toggle(100);
    calibrateIRSensorsForBlack();
    Buzzer_Toggle(100);

    robot.init();
    //coinDropper.init(COIN_DROPPER_SERVO_PIN);
    //armMechanism.init(ARM_LIFT_SERVO_PIN, GRIPPER_SERVO_PIN);

    robot.set_task(MovetoMaze);
    

    //menu.begin();


    delay(5000);
    
    

    Buzzer_UniquePattern();
    //doTasks();  
    
    //FollowColorLineUntilJunction();
    //exectute_colorLineFollowing();

    
}


void loop() {
    
    // Serial2.print(getAverageSensorReading(LEFT_MARKER_SENSOR, 5));
    // Serial2.print(", ");
    // Serial2.println(getAverageSensorReading(RIGHT_MARKER_SENSOR, 5));
    
    //printIRData();

    // mux.selectChannel(0); // channel 0 is selected for OLED
    // menu.handleInput(BUTTON_UP, BUTTON_DOWN, BUTTON_SELECT);//MenuSelectioninitiated 
    //Serial2.println(robot.get_front_distance_from_middle_tof());
    //Junction junction = Detect_Junction_type_on_Color_line();
    
    //Serial2.println(junction);
    FollowBlackLine();

}

