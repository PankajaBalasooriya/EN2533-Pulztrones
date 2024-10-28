#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

// Pin definitions for TCS230 sensors
extern const int leftS0, leftS1, leftS2, leftS3, leftSensorOut;
extern const int middleS0, middleS1, middleS2, middleS3, middleSensorOut;
extern const int rightS0, rightS1, rightS2, rightS3, rightSensorOut;

// Function declarations
void setupSensor(int S0, int S1, int S2, int S3, int sensorOut);

String getLeftColor();
String getMiddleColor();
String getRightColor();
String getColor(int S0, int S1, int S2, int S3, int sensorOut);

#endif // COLOR_H
