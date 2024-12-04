#include "systick.h"

void Systick_begin(){
    Timer1.initialize(20000); // in microseconds
    Timer1.attachInterrupt(Systick_update);
}

void Systick_update(){
    encoders.update();
    motion.update();
    sensors.update();
    //Serial2.println(encoders.robot_speed());

    controller.update_controllers(motion.velocity(), motion.omega(), sensors.get_steering_feedback());
}