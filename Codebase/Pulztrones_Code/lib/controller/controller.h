#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "config.h"
#include "encoders.h"
#include "motors.h"
#include "motion.h"

class Controller;

extern Controller controller;

class Controller {
 public:
  void enable_controllers();
  void disable_controllers();
  void reset_controllers();
  void stop();

  /**
   * At each iteration of the main control loop we need to calculate
   * now outputs form the two position controllers - one for forward
   * motion, one for rotation.
   *
   * The current error increases by an amount determined by the speed
   * and the control loop interval.
   *
   * It is then decreased by the amount the robot has actually moved
   * in the previous loop interval.
   *
   * These changes are both done in the first line.
   *
   * After that we have a simple PD contoller.
   *
   * NOTE: the D-term constant is premultiplied in the config by the
   * loop frequency to save a little time.
   */
  float position_controller();

  /**
   * The rotation controller is exactly like the forward controller
   * except that there is an additional error term from the steering.
   * All steering correction is done by treating the error term as an
   * angular velocity. Depending on your method of analysis, you might
   * also try feeding the steering corection back as an angular
   * acceleration.
   *
   * If you have a gyro, you can use the output from that instead of
   * the encoders.
   *
   * A separate controller calculates the steering adjustment term.
   */
  float angle_controller(float steering_adjustment);

  /**
   * Calculate the outputs of the feedback and feedforward controllers
   * for both forward and rotation, and combine them to obtain drive
   * voltages for the left and right motors.
   */
  void update_controllers(float velocity, float omega, float steering_adjustment);

  float calculate_steering_adjustment(float error);
  

  /**
   * Feed forward attempts to work out what voltage the motors would need
   * to run at the current speed and acceleration.
   *
   * Without this, the controller has a lot of work to do and will be
   * much harder to tune for good performance.
   *
   * The drive train is not symmetric and there is significant stiction.
   * If used with PID, a simpler, single value will be sufficient.
   *
   */
  float leftFeedForward(float speed);
  float rightFeedForward(float speed);

  /**
   * Once the motor voltages have been calculated, they need to be converted
   * into suitable PWM values for the motor drivers.
   *
   * In this section, the calculations for that are done, taking into account
   * the available battery voltage and the limits of the PWM hardware.
   *
   * If there is not enough voltage available from the battery, the output
   * will just saturate and the motor will not get up to speed.
   *
   * Some people add code to light up an LED whenever the drive output is
   * saturated.
   */
  int pwm_compensated(float desired_voltage, float battery_voltage);
  void set_left_motor_volts(float volts);
  void set_right_motor_volts(float volts);
  
  void set_left_motor_pwm(int pwm);
  void set_right_motor_pwm(int pwm);

  /**
   * These getters are used for logging and debugging.
   */
  int get_fwd_millivolts();
  int get_rot_millivolts();
  float get_left_motor_volts();
  float get_right_motor_volts();
  void set_speeds(float velocity, float omega); 


  

 private:
  bool r_controller_output_enabled = true;
  bool r_feedforward_enabled = false;
  float r_previous_fwd_error = 0;
  float r_previous_rot_error = 0;
  float r_previous_steering_error = 0;
  float r_fwd_error = 0;
  float r_rot_error = 0;
  float r_velocity = 0;
  float r_omega = 0;
  // these are maintained only for logging
  float r_left_motor_volts = 0;
  float r_right_motor_volts = 0;
};


#endif



