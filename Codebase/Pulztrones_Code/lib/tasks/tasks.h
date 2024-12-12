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



class Tasks {
public:
    static void start_square();
    static int  Counting_and_Line_Navigation();
    static void bar_code();
    static void execute_MoveToMaze();
    static void execute_maze(int VB_POS);
    static void executeColorLine();
    static void executeDashedLine();
    static void executePortalNavigation();
    static void executeBoxArranging();
    static void executeChamberInsertion();
    static void executeHiddenTask();
    static void executeUnevenTerrain();
};
#endif // TASKS_H
