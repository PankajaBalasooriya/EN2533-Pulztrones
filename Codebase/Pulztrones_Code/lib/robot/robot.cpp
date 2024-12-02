#include "robot.h"
#include "motion.h"
#include "config.h"

Robot::Robot() {
    // Initialize the robot
    init();
}

void Robot::init(){
    
};

void turn_IP180() {
    static int direction = 1;
    direction *= -1;  // alternate direction each time it is called
    motion.spin_turn(direction * 180, OMEGA_SPIN_TURN, ALPHA_SPIN_TURN);
  }

void turn_IP90R() {
    motion.spin_turn(-90, OMEGA_SPIN_TURN, ALPHA_SPIN_TURN);
  }

  void turn_IP90L() {
    motion.spin_turn(90, OMEGA_SPIN_TURN, ALPHA_SPIN_TURN);
  }