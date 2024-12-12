
#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

// Pin definitions for the TCS230 sensor
extern const int leftS0, leftS1, leftS2, leftS3, leftSensorOut;

// Adjustable thresholds for red and blue detection
extern int redThreshold[3][2];
extern int blueThreshold[3][2];

// Function declarations
void setupSensor(int S0, int S1, int S2, int S3, int sensorOut);
void readRGB(int S0, int S1, int S2, int S3, int sensorOut, int &red, int &green, int &blue);
String detectColor(int red, int green, int blue);

#endif

