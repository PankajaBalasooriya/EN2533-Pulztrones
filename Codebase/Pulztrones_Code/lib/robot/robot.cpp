#include "robot.h"



Robot::Robot() {
    // Initialize the robot
    init();
}

void Robot::init(){
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    pinMode(BUTTON_DOWN, INPUT);
    pinMode(BUTTON_SELECT, INPUT);
    pinMode(BUTTON_UP, INPUT);


    pinMode(COIN_DROPPER_ON_PIN, OUTPUT);
    pinMode(ARM_GRIPPER_ON_PIN, OUTPUT);
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


void Robot::pick_virtual_box(){
    robot.turn_on_led(BLUE_LED);
    Buzzer_Toggle(100);
    delay(200);
}

void Robot::drop_virtual_box(){
    robot.turn_off_led(BLUE_LED);
    Buzzer_Toggle(100);
    delay(200); 
}

void Robot::pick_box_and_lift(ArmMechanism &armMechanism){
    armMechanism.holdBox();
    armMechanism.moveToPickupPosition();
}

void Robot::drop_box_and_release(ArmMechanism &armMechanism){
    armMechanism.moveToRestPosition();
    armMechanism.openGripper();
}

int Robot::check_for_left_wall(Ultrasonic &ultrasonic){
    const int ARRAY_SIZE = 5;
    float distanceArray[ARRAY_SIZE];

    // Measure multiple distances
    ultrasonic.measureDistances(distanceArray, ARRAY_SIZE);
  
    // Check if the path is blocked
    int isBlocked = ultrasonic.BlockedOrNot(distanceArray, ARRAY_SIZE);
    return isBlocked;
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