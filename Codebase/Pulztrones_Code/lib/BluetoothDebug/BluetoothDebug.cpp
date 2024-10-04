#include "BluetoothDebug.h"

// Initialize Bluetooth communication on Serial2
void initBluetoothDebug(long baudRate) {
    Serial2.begin(baudRate);  // Initialize Bluetooth at the specified baud rate
    Serial.begin(9600);       // Initialize Serial for USB communication
    delay(1000);              // Give time for everything to initialize
    Serial.println("Bluetooth Debugging Ready!");
}


// Function to send data via Bluetooth
void sendBluetoothData(String data) {
    Serial2.println(data);
}

// Function to log data to the Serial Monitor
void logToMonitor(String data) {
    Serial.println(data);
}
