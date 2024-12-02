#include <Arduino.h>
#include "irs.h"

// Define QTR instance and global variables
QTRSensors qtr;
uint16_t sensorValues[SensorCount];  // Define sensorValues with a fixed size

// Initialize the IR sensors
void initIRSensors() {
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
}

bool leftSide = false;
bool rightSide = false;


// Calibrate the IR sensors
void calibrateIRSensors() {
    Serial2.println("Starting calibration...");

    for (uint8_t i = 0; i < 250; i++) {
        qtr.calibrate();
        delay(20);

        // Print the current calibration progress
        if (i % 50 == 0) {  // Print every 50 iterations
            Serial2.print("Calibration progress: ");
            Serial2.print(i);
            Serial2.println("/250");
        }
    }

    Serial2.println("Calibration completed.");
}

// Read black line position
int readBlackLinePosition() {
    return qtr.readLineBlack(sensorValues);
}

int readWhiteLinePosition(){
    return qtr.readLineWhite(sensorValues);
}

float get_steering_feedback(){
    float steering_adjustment = controller.calculate_steering_adjustment(readBlackLinePosition() - 3500);
    return steering_adjustment;
}
    