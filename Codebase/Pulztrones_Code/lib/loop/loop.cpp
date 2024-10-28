#include <Arduino.h>

extern bool T = false;
extern bool L = false;
extern bool R = false;

void timerloop(){
  //updateVelocities();

  int LeftIR, RightIR = analogRead(A8), analogRead(A9);

  if(LeftIR < 100 || RightIR < 100){
    if(LeftIR < 100 && RightIR < 100){
      T = true;
    }
    else if(LeftIR < 100){
      L = true;
    }
    else{
      R = true;
    }
  }
}