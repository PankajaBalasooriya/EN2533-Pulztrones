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
#include "ArmMechanism.h"
#include "CoinDropper.h"
#include "Ultrasonic.h"



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

        void pick_virtual_box();
        void drop_virtual_box();

        void pick_box_and_lift(ArmMechanism &armMechanism);
        void drop_box_and_release(ArmMechanism &armMechanism);

        int check_for_left_wall(Ultrasonic &ultrasonic);
        
    
    private:
        Task task = START_SQUARE;
};



#endif // ROBOT_H