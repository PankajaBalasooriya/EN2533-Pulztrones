#include "BluetoothDebug.h"
#include "encoders.h"
#include "irs.h"
#include "controller.h"

// Initialize Bluetooth communication on Serial2
void initBluetoothDebug(long baudRate) {
    Serial2.begin(baudRate);  // Initialize Bluetooth at the specified baud rate
    delay(1000);              // Give time for everything to initialize
    Serial2.println("Bluetooth Debugging Ready!");
}


// Function to send data via Bluetooth
void sendBluetoothData(String data) {
    Serial2.print(data);
}

void sendBluetoothDataln(String data) {
    Serial2.println(data);
}






/*
void printIRData() {
    // Read QTR sensor values and get the line position
    int16_t position = readBlackLinePosition();

    // Print QTR sensor values to Serial2
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(sensorValues[i]);
        if (i < SensorCount - 1) {
            Serial.print(", ");
        }
    }
    Serial.println();

    delay(100);
}
*/



    
   
