#include "controller.h"



void Controller::enable_controllers() {
  r_controller_output_enabled = true;
}

void Controller::disable_controllers() {
    r_controller_output_enabled = false;
}

void Controller::reset_controllers() {
    r_fwd_error = 0;
    r_rot_error = 0;
    r_previous_fwd_error = 0;
    r_previous_rot_error = 0;
}

void Controller::stop() {
    set_left_motor_volts(0);
    set_right_motor_volts(0);
}

float Controller::position_controller(){
    float increment = r_velocity * LOOP_INTERVAL;
    r_fwd_error += increment - encoders.robot_fwd_change();
    float diff = r_fwd_error - r_previous_fwd_error;
    r_previous_fwd_error = r_fwd_error;
    float output = FWD_KP * r_fwd_error + FWD_KD * diff;
    return output;
}

float Controller::angle_controller(float steering_adjustment) {
    float increment = r_omega * LOOP_INTERVAL;
    r_rot_error += increment - encoders.robot_rot_change();
    r_rot_error += steering_adjustment;
    float diff = r_rot_error - r_previous_rot_error;
    r_previous_rot_error = r_rot_error;
    float output = ROT_KP * r_rot_error + ROT_KD * diff;
    return output;
  }

  //Todo: Implemet feedforward control
  float Controller::leftFeedForward(float speed) {
    static float oldSpeed = speed;
    float leftFF = speed * SPEED_FF;
    if (speed > 0) {
      leftFF += BIAS_FF;
    } else if (speed < 0) {
      leftFF -= BIAS_FF;
    } else {
      // No bias when the speed is 0
    }
    float acc = (speed - oldSpeed) * LOOP_FREQUENCY;
    oldSpeed = speed;
    float accFF = ACC_FF * acc;
    leftFF += accFF;
    return leftFF;
  }

  float Controller::rightFeedForward(float speed) {
    static float oldSpeed = speed;
    float rightFF = speed * SPEED_FF;
    if (speed > 0) {
      rightFF += BIAS_FF;
    } else if (speed < 0) {
      rightFF -= BIAS_FF;
    } else {
      // No bias when the speed is 0
    }
    float acc = (speed - oldSpeed) * LOOP_FREQUENCY;
    oldSpeed = speed;
    float accFF = ACC_FF * acc;
    rightFF += accFF;
    return rightFF;
  }
  




void Controller::update_controllers(float velocity, float omega, float steering_adjustment) {
    r_velocity = velocity;
    r_omega = omega;
    float pos_output = position_controller();
    float rot_output = angle_controller(steering_adjustment);
    float left_output = 0;
    float right_output = 0;
    left_output = pos_output - rot_output;
    right_output = pos_output + rot_output;

    float tangent_speed = r_omega * ROBOT_RADIUS * RADIANS_PER_DEGREE;
    float left_speed = r_velocity - tangent_speed;
    float right_speed = r_velocity + tangent_speed;
    float left_ff = leftFeedForward(left_speed);
    float right_ff = rightFeedForward(right_speed);
    

    if (r_feedforward_enabled) {
      left_output += left_ff;
      right_output += right_ff;
    }
    if (r_controller_output_enabled) {
      //tODO: implement motor output
      set_right_motor_volts(right_output);
      set_left_motor_volts(left_output);
    }
  }

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
  int Controller::pwm_compensated(float desired_voltage, float battery_voltage) {
    int pwm = MOTOR_MAX_PWM * desired_voltage / battery_voltage;
    return pwm;
  }

  void Controller::set_left_motor_volts(float volts) {
    volts = constrain(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
    r_left_motor_volts = volts;
    int motorPWM = pwm_compensated(volts, BATTERY_VOLTAGE);
    controller.set_left_motor_pwm(motorPWM);
  }

  void Controller::set_right_motor_volts(float volts) {
    volts = constrain(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
    r_right_motor_volts = volts;
    int motorPWM = pwm_compensated(volts, BATTERY_VOLTAGE);
    controller.set_right_motor_pwm(motorPWM);
  }

  void Controller::set_left_motor_pwm(int pwm) {
    pwm = MOTOR_LEFT_POLARITY * constrain(pwm, -MOTOR_MAX_PWM, MOTOR_MAX_PWM);
    setMotorLPWM(pwm);
  }
  // TODO: HARDWARE DEPENDENCY
  void Controller::set_right_motor_pwm(int pwm) {
    pwm = MOTOR_RIGHT_POLARITY * constrain(pwm, -MOTOR_MAX_PWM, MOTOR_MAX_PWM);
    setMotorRPWM(pwm);
  }

  /**
   * These getters are used for logging and debugging.
   */
  int Controller::get_fwd_millivolts() {
    return 1000 * (get_right_motor_volts() + get_left_motor_volts());
  }

  int Controller::get_rot_millivolts() {
    return 1000 * (get_right_motor_volts() - get_left_motor_volts());
  }

  float Controller::get_left_motor_volts() {
    float volts = 0;
    ATOMIC {
      volts = r_left_motor_volts;
    }
    return volts;
  }

  float Controller::get_right_motor_volts() {
    float volts = 0;
    ATOMIC {
      volts = r_right_motor_volts;
    }
    return volts;
  }

  void Controller::set_speeds(float velocity, float omega) {
    ATOMIC {
      r_velocity = velocity;
      r_omega = omega;
    }
  }