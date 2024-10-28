#include "color.h"

// Pin definitions for TCS230 sensors
const int leftS0 = 28, leftS1 = 29, leftS2 = 30, leftS3 = 31, leftSensorOut = 34;
const int middleS0 = 35, middleS1 = 36, middleS2 = 37, middleS3 = 38, middleSensorOut = 33;
const int rightS0 = 39, rightS1 = 40, rightS2 = 41, rightS3 = 42, rightSensorOut = 32;

// Initialize each sensor
void setupSensor(int S0, int S1, int S2, int S3, int sensorOut) {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

// Function to read color from the left sensor
String getLeftColor() {
  return getColor(leftS0, leftS1, leftS2, leftS3, leftSensorOut);
}

// Function to read color from the middle sensor
String getMiddleColor() {
  return getColor(middleS0, middleS1, middleS2, middleS3, middleSensorOut);
}

// Function to read color from the right sensor
String getRightColor() {
  return getColor(rightS0, rightS1, rightS2, rightS3, rightSensorOut);
}

// General color detection function based on sensor values
String getColor(int S0, int S1, int S2, int S3, int sensorOut) {
  // Reading Red Frequency
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int red = pulseIn(sensorOut, LOW);
  delay(100);

  // Reading Green Frequency
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int green = pulseIn(sensorOut, LOW);
  delay(100);

  // Reading Blue Frequency
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blue = pulseIn(sensorOut, LOW);
  delay(100);

  // Color detection based on sensor values
  if (red >= 25 && red <= 100 && green >= 110 && green <= 270 && blue >= 80 && blue <= 195) {
    return "RED";
  }
  else if (red >= 100 && red <= 310 && green >= 80 && green <= 290 && blue >= 30 && blue <= 130) {
    return "BLUE";
  }
  else if (red >= 150 && red <= 350 && green >= 175 && green <= 400 && blue >= 150 && blue <= 270) {
    return "BLACK";
  }
  else if (red >= 5 && red <= 100 && green >= 15 && green <= 110 && blue >= 10 && blue <= 110) {
    return "WHITE";
  }
  else {
    return "UNKNOWN";
  }
}

