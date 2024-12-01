#include "profile.h"

Profile forward;
Profile rotation;

void Profile::reset(){
    ATOMIC {
      r_position = 0;
      r_speed = 0;
      r_target_speed = 0;
      r_state = PS_IDLE;
    }
}

bool Profile::is_finished(){
    return r_state == PS_FINISHED;
}

void Profile::start(float distance, float top_speed, float final_speed, float acceleration){
    r_sign = (distance < 0) ? -1 : 1;
    if (distance < 0) distance = -distance;
    if (distance < 1.0){
        r_state = PS_FINISHED;
        return;
    }
    if(final_speed > top_speed){
        final_speed = top_speed;
    }

    r_position = 0;
    r_final_position = distance;
    r_target_speed = r_sign * fabsf(top_speed);
    r_final_speed = r_sign * fabsf(final_speed);
    r_acceleration = fabsf(acceleration);

    if(r_acceleration >=1){
        r_one_over_acc = 1.0f / r_acceleration;
    }
    else{
        r_one_over_acc = 1.0;
    }
    r_state = PS_ACCELERATING;
}

void Profile::move(float distance, float top_speed, float final_speed, float acceleration){
    start(distance, top_speed, final_speed, acceleration);
    wait_until_finished();
}

void Profile::wait_until_finished() {
    while (r_state != PS_FINISHED) {
      delay(2);
    }
}

void Profile::stop() {
    ATOMIC {
      r_target_speed = 0;
    }
    finish();
  }

  void Profile::finish() {
    ATOMIC {
      r_speed = r_target_speed;
      r_state = PS_FINISHED;
    }
  }

  void Profile::set_state(State state) {
    r_state = state;
  }

  float Profile::get_braking_distance() {
    return fabsf(r_speed * r_speed - r_final_speed * r_final_speed) * 0.5 * r_one_over_acc;  // v^2 = u^2 + 2as
  }

  float Profile::position() {
    float pos;
    ATOMIC {
      pos = r_position;
    }
    return pos;
  }


  float Profile::speed() {
    float speed;
    ATOMIC {
      speed = r_speed;
    }
    return speed;
  }

  float Profile::acceleration() {
    float acc;
    ATOMIC {
      acc = r_acceleration;
    }
    return acc;
  }

  void Profile::set_speed(float speed) {
    ATOMIC {
      r_speed = speed;
    }
  }
  void Profile::set_target_speed(float speed) {
    ATOMIC {
      r_target_speed = speed;
  }
  }

  // normally only used to alter position for forward error correction
  void Profile::adjust_position(float adjustment) {
    ATOMIC {
      r_position += adjustment;
    }
  }

  void Profile::set_position(float position) {
    ATOMIC {
      r_position = position;
    }
  }

  void Profile::update() {
    if (r_state == PS_IDLE) {
      return;
    }
    float delta_v = r_acceleration * LOOP_INTERVAL;
    float remaining = fabsf(r_final_position) - fabsf(r_position);
    if (r_state == PS_ACCELERATING) {
      if (remaining < get_braking_distance()) {
        r_state = PS_BRAKING;
        if (r_final_speed == 0) {
          r_target_speed = r_sign * 5.0f;  
        } else {
          r_target_speed = r_final_speed;
        };
      }
    }
    // try to reach the target speed
    if (r_speed < r_target_speed) {
      r_speed += delta_v;
      if (r_speed > r_target_speed) {
        r_speed = r_target_speed;
      }
    }
    if (r_speed > r_target_speed) {
      r_speed -= delta_v;
      if (r_speed < r_target_speed) {
        r_speed = r_target_speed;
      }
    }
    // increment the position
    r_position += r_speed * LOOP_INTERVAL;
  
    if (r_state != PS_FINISHED && remaining < 0.125) {
      r_state = PS_FINISHED;
      r_target_speed = r_final_speed;
    }
  }