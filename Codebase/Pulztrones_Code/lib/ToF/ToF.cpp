#include "ToF.h"


VL53L0X_Multiplexer::VL53L0X_Multiplexer(uint8_t multiplexerAddress) {
  tcaAddr = multiplexerAddress;
}

// Initialize the sensors
void VL53L0X_Multiplexer::begin() {
  Wire.begin();

  // Initialize each sensor on the respective channel // need to find the positions of the sensors
  tcaSelect(2);
  sensor1.init();
  sensor1.setTimeout(250);

  tcaSelect(3);
  sensor2.init();
  sensor2.setTimeout(250);

  tcaSelect(4);
  sensor3.init();
  sensor3.setTimeout(250);

  Serial.println("VL53L0X Sensors Initialized");
}

// Function to select TCA9548A channel
void VL53L0X_Multiplexer::tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(tcaAddr);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

// Function to get distance from the specified sensor channel
uint16_t VL53L0X_Multiplexer::getTofDistance(uint8_t sensorChannel) {
  uint16_t distance = 0;

  switch (sensorChannel) {
    case 2:
      tcaSelect(2);
      distance = sensor1.readRangeSingleMillimeters();
      if (sensor1.timeoutOccurred()) {
        Serial.println("Sensor 1 timeout!");
      }
      break;

    case 3:
      tcaSelect(3);
      distance = sensor2.readRangeSingleMillimeters();
      if (sensor2.timeoutOccurred()) {
        Serial.println("Sensor 2 timeout!");
      }
      break;

    case 4:
      tcaSelect(4);
      distance = sensor3.readRangeSingleMillimeters();
      if (sensor3.timeoutOccurred()) {
        Serial.println("Sensor 3 timeout!");
      }
      break;

    default:
      Serial.println("Invalid sensor channel");
      break;
  }

  return distance;
}
