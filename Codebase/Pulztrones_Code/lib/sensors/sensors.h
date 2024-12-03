#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "irs.h"
#include "config.h"

enum {
  LINE_FOLLOW,
  STEER_NORMAL
};

class Sensors {
    public:
    /*** steering variables ***/
    uint8_t g_steering_mode = STEER_NORMAL;

    float get_steering_feedback();
    float get_cross_track_error();

    /**
   * The steering adjustment is an angular error that is added to the
   * current encoder angle so that the robot can be kept central in
   * a maze cell.
   *
   * A PD controller is used to generate the adjustment and the two constants
   * will need to be adjusted for the best response. You may find that only
   * the P term is needed
   *
   * The steering adjustment is limited to prevent over-correction. You should
   * experiment with that as well.
   *
   * @brief Calculate the steering adjustment from the cross-track error.
   * @param error calculated from wall sensors, Negative if too far right
   * @return steering adjustment in degrees
   *
   * TODO: It is not clear that this belongs here rather tham for example,
   *       in a Robot class.
   */
  float calculate_steering_adjustment();

  void set_steering_mode(uint8_t mode);

  /*********************************** Wall tracking **************************/
  // calculate the alignment errors - too far left is negative

  /***
   * Note: Runs from the systick interrupt. DO NOT call this directly.
   * @brief update the global wall sensor values.
   * @return robot cross-track-error. Too far left is negative.
   */
  void update();

       
    private:
        float r_last_steering_error = 0;
        volatile bool r_active = false;
        volatile float r_cross_track_error = 0;
        volatile float r_steering_adjustment = 0;
};

#endif