#ifndef SYSTICK_H
#define SYSTICK_H

#include <Arduino.h>
#include "config.h"
#include "motion.h"
#include "motors.h"
#include "controller.h"

class Systick {
public:
    // Initialize the systick timer
    void begin();

    void NewFunction();

    // Update method for time-critical control functions
    void update();
};

extern Systick systick;

#endif // SYSTICK_H