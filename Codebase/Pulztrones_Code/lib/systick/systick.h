#ifndef SYSTICK_H
#define SYSTICK_H

#include <Arduino.h>
#include "controller.h"
#include "BluetoothDebug.h"
#include "TimerOne.h"
#include "motion.h"
#include "encoders.h"
#include "irs.h"
#include "sensors.h"
#include "reporting.h"

void Systick_begin();
void Systick_update();

#endif