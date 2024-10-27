// src/ColorSensor.cpp
#include "ColorSensor.h"

ColorSensor::ColorSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out) {
    _s0 = s0;
    _s1 = s1;
    _s2 = s2;
    _s3 = s3;
    _sensorOut = out;
}

void ColorSensor::begin() {
    pinMode(_s0, OUTPUT);
    pinMode(_s1, OUTPUT);
    pinMode(_s2, OUTPUT);
    pinMode(_s3, OUTPUT);
    pinMode(_sensorOut, INPUT);
    
    // Setting frequency scaling to 20%
    digitalWrite(_s0, HIGH);
    digitalWrite(_s1, LOW);
    
    Serial.println("Color Sensor Starting...");
    calibrate();
    Serial.println("Calibration Complete!");
}

void ColorSensor::calibrate() {
    Serial.println("Hold white paper for calibration...");
    delay(2000); // Give time to position white paper
    
    // Reset min/max values
    redMin = 9999;
    redMax = 0;
    greenMin = 9999;
    greenMax = 0;
    blueMin = 9999;
    blueMax = 0;
    
    // Calibrate for 5 seconds
    for(int i = 0; i < 50; i++) {
        // Read Red
        int red = readColor(LOW, LOW);
        redMin = min(redMin, red);
        redMax = max(redMax, red);
        
        // Read Green
        int green = readColor(HIGH, HIGH);
        greenMin = min(greenMin, green);
        greenMax = max(greenMax, green);
        
        // Read Blue
        int blue = readColor(LOW, HIGH);
        blueMin = min(blueMin, blue);
        blueMax = max(blueMax, blue);
        
        delay(100);
    }
    
    // Print calibration values for debugging
    Serial.println("Calibration Values:");
    Serial.print("Red Min: "); Serial.print(redMin);
    Serial.print(" Max: "); Serial.println(redMax);
    Serial.print("Green Min: "); Serial.print(greenMin);
    Serial.print(" Max: "); Serial.println(greenMax);
    Serial.print("Blue Min: "); Serial.print(blueMin);
    Serial.print(" Max: "); Serial.println(blueMax);
}

int ColorSensor::readColor(int s2State, int s3State) {
    digitalWrite(_s2, s2State);
    digitalWrite(_s3, s3State);
    return pulseIn(_sensorOut, LOW);
}

String ColorSensor::detectColor() {
    // Read current values
    int redValue = readColor(LOW, LOW);
    int greenValue = readColor(HIGH, HIGH);
    int blueValue = readColor(LOW, HIGH);
    
    // Print raw values for debugging
    Serial.print("Raw - R: "); Serial.print(redValue);
    Serial.print(" G: "); Serial.print(greenValue);
    Serial.print(" B: "); Serial.println(blueValue);
    
    // Calculate how close each color is to its minimum value (inverted percentage)
    // Lower frequency means stronger color presence
    int redStrength = map(redValue, redMax, redMin, 0, 100);
    int greenStrength = map(greenValue, greenMax, greenMin, 0, 100);
    int blueStrength = map(blueValue, blueMax, blueMin, 0, 100);
    
    // Print strength values for debugging
    Serial.print("Strength - R: "); Serial.print(redStrength);
    Serial.print(" G: "); Serial.print(greenStrength);
    Serial.print(" B: "); Serial.println(blueStrength);
    
    // Thresholds for detection
    const int MIN_STRENGTH = 60;      // Minimum strength to detect a color
    const int DOMINANCE_FACTOR = 15;  // How much stronger the dominant color needs to be
    
    // Check for black (high frequency/low strength for all)
    if (redStrength < 20 && greenStrength < 20 && blueStrength < 20) {
        return "BLACK";
    }
    
    // Check for white (low frequency/high strength for all)
    if (redStrength > 80 && greenStrength > 80 && blueStrength > 80) {
        return "WHITE";
    }
    
    // Check for specific colors - the color must be strong and significantly stronger than others
    if (redStrength > MIN_STRENGTH && 
        redStrength > (greenStrength + DOMINANCE_FACTOR) && 
        redStrength > (blueStrength + DOMINANCE_FACTOR)) {
        return "RED";
    }
    
    if (greenStrength > MIN_STRENGTH && 
        greenStrength > (redStrength + DOMINANCE_FACTOR) && 
        greenStrength > (blueStrength + DOMINANCE_FACTOR)) {
        return "GREEN";
    }
    
    if (blueStrength > MIN_STRENGTH && 
        blueStrength > (redStrength + DOMINANCE_FACTOR) && 
        blueStrength > (greenStrength + DOMINANCE_FACTOR)) {
        return "BLUE";
    }
    
    return "UNKNOWN";
}