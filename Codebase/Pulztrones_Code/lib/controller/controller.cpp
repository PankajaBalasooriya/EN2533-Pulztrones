#include "controller.h"
#include "motors.h"
#include "PID.h"
#include "encoders.h"
#include "color.h"
#include "irs.h"

// Constants for robot physical properties
const float WHEEL_DIAMETER_MM = 68.0;
const float WHEEL_BASE_MM = 193.0;
const float COUNTS_PER_REVOLUTION = 824.0;
const float MM_PER_COUNT = (PI * WHEEL_DIAMETER_MM) / COUNTS_PER_REVOLUTION;

const int BASE_SPEED = 80;
const int MAX_SPEED = 120;
const int MIN_SPEED = 50;



