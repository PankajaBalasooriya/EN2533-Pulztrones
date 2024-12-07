// controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

extern int encoder_count_left;
extern int encoder_count_right;



void FollowBlackLine(); 
void FollowWhiteLine();
void MoveDistanceForward(float distance);
void turn(int);

void turn_right_90();
void turn_left_90();
void turn_left_180();

int Counting_and_Line_Navigation();

int binaryToDecimal(int binaryArray[], int arraySize);
int calculateModulo5(int decimalNumber);
#endif
