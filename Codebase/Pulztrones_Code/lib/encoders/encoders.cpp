#include "encoders.h"


Encoders::Encoders(){
    reset();
}

void Encoders::reset() {
    ATOMIC {
      r_left_counter = 0;
      r_right_counter = 0;
      r_robot_distance = 0;
      r_robot_angle = 0;
    }
}

void Encoders::begin(){
    pinMode(ENCODER_LEFT_CLK, INPUT);
    pinMode(ENCODER_LEFT_B, INPUT);
    pinMode(ENCODER_RIGHT_CLK, INPUT);
    pinMode(ENCODER_RIGHT_B, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_CLK), callback_left_encoder_isr, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_CLK), callback_right_encoder_isr, RISING);
    reset();
}

void Encoders::left_input_change() {
    if(digitalRead(ENCODER_LEFT_B) == HIGH){
        r_left_counter++;
    }else{
        r_left_counter--;
    }
}

void Encoders::right_input_change() {
    if(digitalRead(ENCODER_RIGHT_B) == HIGH){
        r_right_counter++;
    }else{
        r_right_counter--;
    }
}


void Encoders::update() {
    int left_delta = 0;
    int right_delta = 0;
    // Make sure values don't change while being read. Be quick.
    ATOMIC {
      left_delta = r_left_counter;
      right_delta = r_right_counter;
      r_left_counter = 0;
      r_right_counter = 0;
    }
    float left_change = left_delta * MM_PER_COUNT_LEFT;
    float right_change = right_delta * MM_PER_COUNT_RIGHT;
    r_fwd_change = 0.5 * (right_change + left_change);
    r_robot_distance += r_fwd_change;
    r_rot_change = (right_change - left_change) * DEG_PER_MM_DIFFERENCE;
    r_robot_angle += r_rot_change;
  }

float Encoders::robot_distance() {
    float distance;
    ATOMIC {
      distance = r_robot_distance;
    }
    return distance;
  }

  float Encoders::robot_speed() {
    float speed;
    ATOMIC {
      speed = LOOP_FREQUENCY * r_fwd_change;
    }
    return speed;
  }

  float Encoders::robot_omega() {
    float omega;
    ATOMIC {
      omega = LOOP_FREQUENCY * r_rot_change;
    }
    return omega;
  }

  float Encoders::robot_fwd_change() {
    float distance;
    ATOMIC {
      distance = r_fwd_change;
    }
    return distance;
  }

  float Encoders::robot_rot_change() {
    float distance;
    ATOMIC {
      distance = r_rot_change;
    }
    return distance;
  }

  float Encoders::robot_angle() {
    float angle;
    ATOMIC {
      angle = r_robot_angle;
    }
    return angle;
  }


   




// Callback functions
void callback_left_encoder_isr() {
    encoders.left_input_change();
}

void callback_right_encoder_isr() {
    encoders.right_input_change();
}