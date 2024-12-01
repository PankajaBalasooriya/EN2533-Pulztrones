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

};



#endif // ROBOT_H