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
    setMotorLPWM(0);
    setMotorRPWM(0);
    r_left_motor_pwm = 0;
    r_right_motor_pwm = 0;
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
    // float left_ff = leftFeedForward(left_speed);
    // float right_ff = rightFeedForward(right_speed);
    float left_ff = left_speed;
    float right_ff = right_speed;

    if (r_feedforward_enabled) {
      left_output += left_ff;
      right_output += right_ff;
    }
    if (r_controller_output_enabled) {
        setMotorRPWM(right_output);
        setMotorLPWM(left_output);
    }
  }