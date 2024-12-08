#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include "robot.h"
#include "motors.h"
#include "encoders.h"
#include "irs.h"
#include "buzzer.h"
#include "config.h"
#include "controller.h"
#include "robot.h"



void start_square();
int Counting_and_Line_Navigation();
void execute_white_line_follow();
void execute_maze();


#endif // TASKS_H
