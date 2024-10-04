#include <Arduino.h>
#include <BluetoothDebug.h>
#include <Adafruit_VL53L0X.h>

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  initBluetoothDebug();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  String debugInfo = "Starting.......";  
  sendBluetoothData(debugInfo);

  delay(1000);
}

// put function definitions here:
