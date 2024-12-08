// controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "config.h"
#include "irs.h"

extern int encoder_count_left;
extern int encoder_count_right;



void FollowBlackLine(); 
void FollowWhiteLine();
//void FollowWhiteLine_Distance(int distance);
void FollowWhiteLine_GivenDistance(int distance);
void FollowBlackLine_GivenDistance(int distance);
Junction FollowWhiteLineUntilJunction();

void MoveDistanceForward(float distance);
void turn(int);

void turn_right_90();
void turn_left_90();
void turn_left_180();

int Counting_and_Line_Navigation();


#endif
