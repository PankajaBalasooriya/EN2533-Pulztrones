#ifndef box_manulipation_H
#define box_manulipation_H

#include <Arduino.h>
#include "config.h"

int find_destination();
int meassure_box_height();
void goto_box_destination(int dest);

#endif