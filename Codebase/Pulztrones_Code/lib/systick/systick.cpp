#include "systick.h"

int left_count = 0;
int right_count = 0;

void Systick_begin(){
    Timer1.initialize(20000); // in microseconds
    Timer1.attachInterrupt(Systick_update);
}

void Systick_update(){
    encoders.update();
    //encoders.getCounts(left_count, right_count);
    motion.update();
    sensors.update();
    Serial2.print(">");
    Serial2.print("Speed:");
    Serial2.println(encoders.robot_speed());
    

    //controller.update_controllers(motion.velocity(), motion.omega(), sensors.get_steering_feedback());
    //reporter.report_profile();
}