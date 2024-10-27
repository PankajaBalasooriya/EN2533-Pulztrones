// include/ColorSensor.h
#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Arduino.h>

class ColorSensor {
public:
    ColorSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out);
    void begin();
    String detectColor();
    void calibrate();
    
private:
    uint8_t _s0, _s1, _s2, _s3, _sensorOut;
    int redMin, redMax;
    int greenMin, greenMax;
    int blueMin, blueMax;
    
    int readColor(int s2State, int s3State);
};

#endif