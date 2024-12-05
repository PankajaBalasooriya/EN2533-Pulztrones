#ifndef REPORTER_H
#define REPORTER_H

#include <Arduino.h>
#include "encoders.h"
#include "motion.h"
#include "controller.h"
#include "profile.h"
#include "sensors.h"

//enum MazeView { PLAIN, COSTS, DIRS };

//extern const char dir_letters[];
//extern const char hdg_letters[];

class Reporter {
private:
  uint32_t s_start_time = millis();
  uint32_t s_report_time = millis();
  uint32_t s_report_interval = REPORTING_INTERVAL;

public:
  void set_printer(Stream& stream);

  // Formatting methods
  void print_justified(int32_t value, int width);

  // Profile reporting
  void report_profile_header();
  void report_profile();

  // Sensor tracking
  void report_sensor_track_header();
  void report_sensor_track(bool use_raw = false);
  void report_radial_track_header();
  void report_radial_track(bool use_raw = false);
  //void front_sensor_track_header();
  //void front_sensor_track();

  // Sensor and wall reporting
  //void wall_sensor_header();
  //void print_wall_sensors();
  //void print_walls();

  // Action logging
  //void log_action_status(char action, char note, Location location, Heading heading);

  // ADC and diagnostic methods
  //void show_adc();

  // Maze printing
  //void print_h_wall(uint8_t state);
  //void printNorthWalls(int y);
  //void printSouthWalls(int y);
  // print_maze(int style = PLAIN);
};


extern Reporter reporter;

#endif // REPORTER_H