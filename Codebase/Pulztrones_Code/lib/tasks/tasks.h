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
#include "box_manupilation.h"
#include "ArmMechanism.h"
#include "CoinDropper.h"

extern ArmMechanism armMechanism;


void start_square();
int Counting_and_Line_Navigation();
void execute_MoveToMaze();
void execute_maze(int VB_POS);
String exectute_colorLineFollowing();
void execute_box_manup(int assending);



//other functions needed
void box_in_lower_position();
void box_upper_position();
void blue_open();
#endif // TASKS_H
