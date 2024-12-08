// controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "config.h"
#include "irs.h"

extern int encoder_count_left;
extern int encoder_count_right;

extern float error_enc;
extern float correction_enc;



void FollowBlackLine(); 
void FollowWhiteLine();
//void FollowWhiteLine_Distance(int distance);
void FollowWhiteLine_GivenDistance(int distance);
void FollowBlackLine_GivenDistance(int distance);
Junction FollowWhiteLineUntilJunction();

void MoveDistanceForward(float distance);
void turn(int);

void turnRight90();
void turnLeft90();
void turnLeft180();

int Counting_and_Line_Navigation();


#endif
