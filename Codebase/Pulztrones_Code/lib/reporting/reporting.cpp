#include "reporting.h"

static Stream& printer = Serial2;

//Reporter reporter;

void Reporter::set_printer(Stream& stream) {
  printer = stream;
}

void Reporter::print_justified(int32_t value, int width) {
    int v = value;
    int w = width;
    w--;
    if (v < 0) {
      w--;
    }
    while (v /= 10) {
      w--;
    }
    while (w > 0) {
      printer.write(' ');
      --w;
    }
    printer.print(value);
  }


   /**
   * The profile reporter will send out a table of space separated
   * data so that the results can be saved to a file or imported to
   * a spreadsheet or other analyss software.
   *
   * Always send the header first because that restarts the elapsed
   * time count.
   *
   * The data includes
   *   time        - in milliseconds since the header was sent
   *   robotPos    - position in mm as reported by the encoders
   *   robotAngle  - angle in degrees as reported by the encoders
   *   fwdPos      - forward profiler setpoint in mm
   *   fwdSpeed    - forward profiler current speed in mm/s
   *   rotpos      - rotation profiler setpoint in deg
   *   rotSpeed    - rotation profiler current speed in deg/s
   *   fwdmVolts    - voltage sent to the motors for forward control
   *   rotmVolts    - voltage sent to the motors for rotation control
   *
   */
  void Reporter::report_profile_header() {
    printer.println(F("time robotPos robotAngle fwdPos  fwdSpeed rotpos rotSpeed fwdmVolts rotmVolts"));
    s_start_time = millis();
    s_report_time = s_start_time;
  }

  void Reporter::report_profile() {
    if (millis() >= s_report_time) {
      s_report_time += s_report_interval;
      print_justified(int(encoders.robot_distance()), 6);
      print_justified(int(encoders.robot_angle()), 6);
      print_justified(int(motion.position()), 6);
      print_justified(int(motion.velocity()), 6);
      print_justified(int(motion.angle()), 6);
      print_justified(int(motion.omega()), 6);
      print_justified(controller.get_fwd_millivolts(), 6);
      print_justified(controller.get_rot_millivolts(), 6);
      printer.println();
    }
  }

  /***
   * The full sensor track report can be used to help calibrate the sensors and
   * check the operation of the steering.
   *
   * You could also use it to examine the sensor readings as walls are detected or lost.
   *
   * To avoid sending more data that is needed, the default is to send only the
   * normalised sensor readings. Call with the argument set true to see raw sensor
   * readings for calibration checks.
   *
   */
  void Reporter::report_sensor_track_header() {
    printer.println(F(" time pos angle cte steer"));
    s_start_time = millis();
    s_report_time = s_start_time;
  }

  void Reporter::report_sensor_track(bool use_raw = false) {
    if (millis() >= s_report_time) {
      s_report_time += s_report_interval;
      print_justified(int(millis() - s_start_time), 6);
      print_justified(int(encoders.robot_distance()), 6);
      print_justified(int(encoders.robot_angle()), 6);
      printer.print(' ');
      printer.print(sensors.get_cross_track_error());
      printer.print(' ');
      printer.print(sensors.get_steering_feedback());
      printer.println();
    }
  }

  void Reporter::report_radial_track_header() {
    printer.println(F(" angle cte steer"));
    s_start_time = millis();
    s_report_time = s_start_time;
  }
  void Reporter::report_radial_track(bool use_raw = false) {
    static int recorded_angle = INT16_MAX;
    int this_angle = (int)encoders.robot_angle();
    if (recorded_angle != this_angle) {
      recorded_angle = this_angle;
      print_justified(recorded_angle, 6);
      printer.print(' ');
      printer.print(sensors.get_cross_track_error());
      printer.print(' ');
      printer.print(sensors.get_steering_feedback());
      printer.println();
    }
  }

  //TODO: Implement the ir sensor reporting.
