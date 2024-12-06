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

  //Todo: impelemt for white black and color steering + implement without using the library
  // line following error
  int Sensors::normal_steering_error(){

    if (g_steering_mode == WHITE_LINE_FOLLOW) {
      return readWhiteLinePosition() - 3500;
    } else if (g_steering_mode == BLACK_LINE_FOLLOW) {
      return readBlackLinePosition() - 3500;
    } else
    {
      return 0;
    }
  }



  void Sensors::update(){
    // calculate the alignment errors - too far left is negative
    r_cross_track_error = -1 * normal_steering_error();
    calculate_steering_adjustment();
  }