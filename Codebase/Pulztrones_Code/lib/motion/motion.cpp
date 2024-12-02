#include "motion.h"

void Motion::reset_drive_system() {
    controller.stop();
    controller.disable_controllers();
    encoders.reset();
    forward.reset();
    rotation.reset();
    controller.reset_controllers();
    controller.enable_controllers();
}

void Motion::stop() {
    controller.stop();
}

void Motion::disable_drive() {
    controller.disable_controllers();
}

float Motion::position() {
    return forward.position();
}

float Motion::velocity() {
    return forward.speed();
}

float Motion::acceleration() {
    return forward.acceleration();
}

void Motion::set_target_velocity(float velocity) {
    forward.set_target_speed(velocity);
}

float Motion::angle() {
    return rotation.position();
}

float Motion::omega() {
    return rotation.speed();
}

float Motion::alpha() {
    return rotation.acceleration();
}

void Motion::start_move(float distance, float top_speed, float final_speed, float acceleration) {
    forward.start(distance, top_speed, final_speed, acceleration);
}

bool Motion::move_finished() {
    return forward.is_finished();
}

void Motion::move(float distance, float top_speed, float final_speed, float acceleration) {
    forward.move(distance, top_speed, final_speed, acceleration);
}

void Motion::start_turn(float distance, float top_speed, float final_speed, float acceleration) {
    rotation.start(distance, top_speed, final_speed, acceleration);
}

bool Motion::turn_finished() {
    return rotation.is_finished();
}

void Motion::turn(float distance, float top_speed, float final_speed, float acceleration) {
    rotation.move(distance, top_speed, final_speed, acceleration);
}

void Motion::update() {
    forward.update();
    rotation.update();
}

void Motion::set_position(float pos) {
    forward.set_position(pos);
}

void Motion::adjust_forward_position(float delta) {
    forward.adjust_position(delta);
}

void Motion::turn(float angle, float omega, float alpha) {
    // get ready to turn
    rotation.reset();
    rotation.move(angle, omega, 0, alpha);
}

void Motion::spin_turn(float angle, float omega, float alpha) {
    forward.set_target_speed(0);
    while (forward.speed() != 0) {
        delay(2);
    }
    turn(angle, omega, alpha);
}

void Motion::stop_at(float position) {
    float remaining = position - forward.position();
    forward.move(remaining, forward.speed(), 0, forward.acceleration());
}

void Motion::stop_after(float distance) {
    forward.move(distance, forward.speed(), 0, forward.acceleration());
}

void Motion::wait_until_position(float position) {
    while (forward.position() < position) {
        delay(2);
    }
}

void Motion::wait_until_distance(float distance) {
    float target = forward.position() + distance;
    wait_until_position(target);
}
