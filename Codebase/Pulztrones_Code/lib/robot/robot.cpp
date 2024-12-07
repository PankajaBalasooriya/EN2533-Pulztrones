#include "robot.h"



Robot::Robot() {
    // Initialize the robot
    init();
}

void Robot::init(){
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
};

void Robot::set_task(Task task) {
    task = task;
  }

void Robot::turn_right_90(){
    turn_right_90();
}

void Robot::turn_left_90(){
    turn_left_90();
}

void Robot::turn_left_180(){
    turn_left_180();
}
//TODO: BLUE LED Not turning on
void Robot::turn_on_led(int PIN) {
    digitalWrite(PIN, HIGH);
}

void Robot::turn_off_led(int PIN) {
    digitalWrite(PIN, LOW);
}







//***** Feature Testing code *****************************************************//
void Robot::turn_on_LEDS(){
    robot.turn_on_led(RED_LED);
    robot.turn_on_led(BLUE_LED);
}

void Robot::turn_off_LEDS(){
    robot.turn_off_led(RED_LED);
    robot.turn_off_led(BLUE_LED);
}