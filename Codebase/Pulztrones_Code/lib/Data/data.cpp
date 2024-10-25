#include <Arduino.h>
#include "data.h"
#include "encoders.h"
#include "irs.h"


void printEncoderData() {
    static unsigned long lastPrintTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastPrintTime >= 100) {
        Serial2.print("Left Encoder: ");
        Serial2.print(getLeftEncoderCounts());
        Serial2.print(", Right Encoder: ");
        Serial2.println(getRightEncoderCounts());
        lastPrintTime = currentTime;
    }
}

void printIRData() {
    // Read QTR sensor values and get the line position
    int16_t position = readBlackLinePosition();

    // Print QTR sensor values to Serial2
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial2.print(sensorValues[i]);
        if (i < SensorCount - 1) {
            Serial2.print(", ");
        }
    }
    Serial2.println();

    delay(100);
}