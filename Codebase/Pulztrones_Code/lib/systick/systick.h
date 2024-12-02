#ifndef SYSTICK_H
#define SYSTICK_H

#include <Arduino.h>
#include "config.h"
#include "motion.h"
#include "motors.h"
#include "controller.h"
#include "irs.h"
class Systick {
public:
    // Initialize the systick timer
    void begin();



    // Update method for time-critical control functions
    void update();
};



#endif // SYSTICK_H