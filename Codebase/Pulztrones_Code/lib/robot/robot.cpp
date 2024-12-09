#include "robot.h"



Robot::Robot() {
    // Initialize the robot
    init();
}

void Robot::init(){
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
};

void Robot::set_task(Task newtask) {
    task = newtask;
  }

void Robot::turn_right_90(){
    turnRight90();
}

void Robot::turn_left_90(){
    turnLeft90();
}

void Robot::turn_left_180(){
    turnLeft180();
}
//TODO: BLUE LED Not turning on
void Robot::turn_on_led(int PIN) {
    digitalWrite(PIN, HIGH);
}

void Robot::turn_off_led(int PIN) {
    digitalWrite(PIN, LOW);
}



Task Robot::get_task(){
    return task;
}

//Todo: switch this to Blue led when it is fixed
void Robot::pick_virtual_box(){
    robot.turn_on_led(RED_LED);
    Buzzer_Toggle(100);
    delay(200);
}

void Robot::drop_virtual_box(){
    robot.turn_off_led(RED_LED);
    Buzzer_Toggle(100);
    delay(200); 
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