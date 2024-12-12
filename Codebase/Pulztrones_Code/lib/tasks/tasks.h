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
#include "I2CMUX.h"
#include "ToF.h"



void start_square();
int Counting_and_Line_Navigation();
void execute_MoveToMaze();
void execute_maze(int VB_POS);
void blue_open();



//other functions needed
void box_in_lower_position();
void box_upper_position();
#endif // TASKS_H
