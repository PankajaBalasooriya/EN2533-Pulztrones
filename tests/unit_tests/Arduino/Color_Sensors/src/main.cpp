// src/main.cpp
#include <Arduino.h>
#include "ColorSensor.h"

// Define pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Create color sensor instance
ColorSensor colorSensor(S0, S1, S2, S3, sensorOut);

void setup() {
    Serial.begin(9600);
    colorSensor.begin();  // This will also perform calibration
}

void loop() {
    String detectedColor = colorSensor.detectColor();
    Serial.print("Detected Color: ");
    Serial.println(detectedColor);
    delay(500);
}