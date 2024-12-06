#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "irs.h"
#include "buzzer.h"
#include "config.h"
#include "controller.h"

class Robot;
extern Robot robot;

class Robot {
    public:
        enum Task{START_SQUARE,LINE_FOLLOW, BARCODE, STOP};

        Robot();
        void init();

        void set_task(Task task);
        void turn_right_90();
        void turn_left_90();
        void turn_left_180();
        
    
    private:
        volatile int task = LINE_FOLLOW;


};



#endif // ROBOT_H