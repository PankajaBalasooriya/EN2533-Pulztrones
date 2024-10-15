#include "BluetoothDebug.h"

// Initialize Bluetooth communication on Serial2
void initBluetoothDebug(long baudRate) {
    Serial2.begin(baudRate);  // Initialize Bluetooth at the specified baud rate
    delay(1000);              // Give time for everything to initialize
    Serial.println("Bluetooth Debugging Ready!");
}


// Function to send data via Bluetooth
void sendBluetoothData(String data) {
    Serial2.print(data);
}

void sendBluetoothDataln(String data) {
    Serial2.println(data);
}


