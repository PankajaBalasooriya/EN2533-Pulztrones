#include "sensors.h"

float Sensors::get_steering_feedback() {
    return r_steering_adjustment;
  }
  float Sensors::get_cross_track_error() {
    return r_cross_track_error;
  };

  float Sensors::calculate_steering_adjustment() {
    // always calculate the adjustment for testing. It may not get used.
    float pTerm = STEERING_KP * r_cross_track_error;
    float dTerm = STEERING_KD * (r_cross_track_error - r_last_steering_error);
    float adjustment = pTerm + dTerm * LOOP_FREQUENCY;
    adjustment = constrain(adjustment, -STEERING_ADJUST_LIMIT, STEERING_ADJUST_LIMIT);
    r_last_steering_error = r_cross_track_error;
    r_steering_adjustment = adjustment;
    return adjustment;
  }

  void Sensors::set_steering_mode(uint8_t mode) {
    r_last_steering_error = r_cross_track_error;
    r_steering_adjustment = 0;
    g_steering_mode = mode;
  }


  void Sensors::update(){
    // calculate the alignment errors - too far left is negative
    //Todo: Implement for white black and steering
    int error = readBlackLinePosition() - 3500;

    r_cross_track_error = error;
    calculate_steering_adjustment();
  }