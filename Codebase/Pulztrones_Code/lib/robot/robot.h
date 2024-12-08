#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "irs.h"
#include "buzzer.h"
#include "config.h"
#include "controller.h"
#include "PID.h"


class Robot;
extern Robot robot;

class Robot {
    public:
        

        Robot();
        void init();

        void set_task(Task newtask);
        void turn_right_90();
        void turn_left_90();
        void turn_left_180();


        void turn_on_led(int PIN);
        void turn_off_led(int PIN);


        
        Task get_task();


        void turn_on_LEDS();
        void turn_off_LEDS();
        
    
    private:
        Task task = START_SQUARE;
};



#endif // ROBOT_H