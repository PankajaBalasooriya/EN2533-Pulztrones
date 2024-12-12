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
void bar_code();
void execute_MoveToMaze();
void execute_maze(int VB_POS);
void executeDashedLine();
void executePortalNavigation();
void executeBoxArranging();
void executeChamberInsertion();
void executeHiddenTask();

#endif // TASKS_H
