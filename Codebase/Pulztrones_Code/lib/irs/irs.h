// irs.h
#ifndef IRS_H
#define IRS_H

#include <QTRSensors.h>

// Declare the QTRSensors instance and functions
extern QTRSensors qtr;
const uint16_t SensorCount = 8;  // Define SensorCount as a constant
extern uint16_t sensorValues[8];  // Use a fixed size for sensorValues

// Function declarations
void initIRSensors();
void calibrateIRSensors();
int readBlackLinePosition();
int readWhiteLinePosition();

#endif
