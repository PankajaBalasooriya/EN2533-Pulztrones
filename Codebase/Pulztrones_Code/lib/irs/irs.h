// irs.h
#ifndef IRS_H
#define IRS_H

#include <QTRSensors.h>
#include "config.h"
#include "motors.h"

// Declare the QTRSensors instance and functions
extern QTRSensors qtr;
extern QTRSensors qtrBack;
const uint16_t SensorCount = 8;  // Define SensorCount as a constant
const uint16_t SensorCountBack = 6;
extern uint16_t sensorValues[8];  // Use a fixed size for sensorValues
extern uint16_t sensorValuesBack[6];


Junction Detect_Junction_type();


// Function declarations
void initIRSensors();
void calibrateIRSensors();
int readBlackLinePosition();
int readWhiteLinePosition();
int readBackWhiteLinePosition();
Junction Detect_Junction_type_on_black_line();
Junction Detect_Junction_type_on_Color_line(int number);
Junction Detect_jun_condition();


#endif
