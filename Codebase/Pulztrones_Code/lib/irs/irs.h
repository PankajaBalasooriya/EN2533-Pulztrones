// irs.h
#ifndef IRS_H
#define IRS_H

#include <QTRSensors.h>

// Declare the QTRSensors instance and functions
extern QTRSensors qtr;
const uint16_t SensorCount = 8;  // Define SensorCount as a constant
extern uint16_t sensorValues[8];  // Use a fixed size for sensorValues

// Add these constants to irs.h
#define JUNCTION_THRESHOLD 50  // Threshold for detecting line presence
#define MIN_SENSORS_FOR_JUNCTION 6  // Minimum number of sensors that must detect line for junction

// Add these function declarations to irs.h
bool isAtJunction();
bool isAtTJunction();
bool isAtLJunction();
void handleJunction(char direction);  // 'L' for left, 'R' for right

// Function declarations
void initIRSensors();
void calibrateIRSensors();
int readBlackLinePosition();
int readWhiteLinePosition();

#endif
