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

Junction Detect_Junction_type(){
    //bool JunctionDetected = false;
    int numberOfSensorsOnWhite = 0;

    for(int i = 0; i < SensorCount; i++){
        if(sensorValues[i] < WHITE_LINE_THRESHOLD){
            numberOfSensorsOnWhite++;
        }
    }

    if(numberOfSensorsOnWhite > SENSORS_ON_LINE_FOR_JUNCTION_CHECK){
        //MotorBreak();
        int leftSensorValue = analogRead(LEFT_MARKER_SENSOR);
        int rightSensorValue = analogRead(RIGHT_MARKER_SENSOR);

        if (leftSensorValue < WHITE_LINE_THRESHOLD && rightSensorValue < WHITE_LINE_THRESHOLD){
            return T_Junction;
        }
        else if (leftSensorValue < WHITE_LINE_THRESHOLD){
            return Left;
        }
        else if (rightSensorValue < WHITE_LINE_THRESHOLD){
            return Right;
        }
        else{
            return Straight;
        }
    }
    else{
        return Straight;
    }
}