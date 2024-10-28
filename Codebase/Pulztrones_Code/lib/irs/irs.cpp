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

bool isAtJunction(int leftIR, int rightIR) {
    // Count how many sensors detect the line
    int sensorsOnLine = 0;
    for (uint8_t i = 0; i < SensorCount; i++) {
        if (sensorValues[i] < JUNCTION_THRESHOLD) {
            sensorsOnLine++;
        }
    }
    
    return sensorsOnLine >= MIN_SENSORS_FOR_JUNCTION;

    // if (leftIR < 100 && rightIR < 100){
    //     return true;
    // }
    // return false;
}

bool isAtTJunction(bool j, int leftIR, int rightIR) {
    // Check if most sensors detect the line (indicating a T junction)
    // return j && sensorValues[0] < JUNCTION_THRESHOLD && 
    //        sensorValues[SensorCount-1] < JUNCTION_THRESHOLD;
    if (leftIR < 100 && rightIR < 100){
        return true;
    }
    return false;
}

bool isAtLJunction(bool j, int leftIR, int rightIR) {
    //For L junction, check if sensors on one side all detect the line
    leftSide = (sensorValues[0] <JUNCTION_THRESHOLD &&
                    sensorValues[1] < JUNCTION_THRESHOLD &&
                    sensorValues[2] < JUNCTION_THRESHOLD);
    
    rightSide = (sensorValues[SensorCount-3] < JUNCTION_THRESHOLD &&
                     sensorValues[SensorCount-2] < JUNCTION_THRESHOLD &&
                     sensorValues[SensorCount-1] < JUNCTION_THRESHOLD);
    
    return j && (leftSide || rightSide);

    // if(leftIR < 100 && rightIR > 100){
    //     leftSide = true;
    //     rightSide = false;
    // }
    // if(rightIR < 100 && leftIR > 100){
    //     rightSide = true;
    //     leftSide = false;
    // }
    // return j && (leftSide || rightSide);
}
