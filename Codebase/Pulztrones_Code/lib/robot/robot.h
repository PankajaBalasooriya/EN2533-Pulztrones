#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "irs.h"
#include "buzzer.h"

class Robot ;
extern Robot robot;

class Robot {
    public:
        enum State{LINE_FOLLOW, BARCODE, STOP};

        Robot();
        void init();

        void turn_IP180();
        void turn_IP90R();
        void turn_IP90L();
        void run(int mm);


};



#endif // ROBOT_H