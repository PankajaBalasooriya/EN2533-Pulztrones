#include "ToFGyroManager.h"

// Constructor
ToFGyroManager::ToFGyroManager(uint8_t pca9548aAddress)
    : pca9548aAddress(pca9548aAddress) {
    for (uint8_t i = 0; i < MAX_TOF_SENSORS; i++) {
        tofInitialized[i] = false;
    }
}

// Select the active channel on the PCA9548A multiplexer
void ToFGyroManager::selectChannel(uint8_t channel) {
    if (channel < 8) {  // Valid channels are 0-7
        Wire.beginTransmission(pca9548aAddress);
        Wire.write(1 << channel);
        Wire.endTransmission();
    }
}

// Initialize all sensors
bool ToFGyroManager::begin() {
    Wire.begin();
    return initializeToFSensors() && initializeGyro();
}

// Initialize ToF sensors
bool ToFGyroManager::initializeToFSensors() {
    for (uint8_t i = 0; i < MAX_TOF_SENSORS; i++) {
        selectChannel(i + 2);  // Channels 2, 3, 4 for ToF sensors
        if (!tofSensors[i].init()) {
            tofInitialized[i] = false;
            return false;
        }
        tofSensors[i].setTimeout(500);
        tofInitialized[i] = true;
    }
    return true;
}

// Initialize Gyro
bool ToFGyroManager::initializeGyro() {
    selectChannel(1);  // Channel 1 for the gyro
    if (!mpu.begin()) {
        return false;
    }
    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ); //sample code from th library use the poper one for the gyro 
    mpu.setMotionDetectionThreshold(1);//change the value if more sensitivity is needed
    //(this is like it calculates the motion when the robot has a unit acc_)
    mpu.setMotionDetectionDuration(20);
    mpu.setInterruptPinLatch(true);
    mpu.setInterruptPinPolarity(true);
    mpu.setMotionInterrupt(true);
    return true;
}

// Get distance from a specific ToF sensor
uint16_t ToFGyroManager::getToFDistance(uint8_t sensorIndex) {
    if (sensorIndex >= MAX_TOF_SENSORS || !tofInitialized[sensorIndex]) {
        return 0xFFFF;  // Invalid sensor index or not initialized
    }
    selectChannel(sensorIndex + 2);
    return tofSensors[sensorIndex].readRangeSingleMillimeters();
}

// Check if a ToF sensor is out of range
bool ToFGyroManager::isToFOutOfRange(uint8_t sensorIndex) {
    if (sensorIndex >= MAX_TOF_SENSORS || !tofInitialized[sensorIndex]) {
        return true;
    }
    selectChannel(sensorIndex + 2);
    return tofSensors[sensorIndex].timeoutOccurred();
}

// Get gyro and accelerometer data
bool ToFGyroManager::getGyroData(float &accX, float &accY, float &accZ, float &gyroX, float &gyroY, float &gyroZ) {
    selectChannel(1);
    if (!mpu.getMotionInterruptStatus()) {
        return false;  // No motion detected
    }

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    accX = a.acceleration.x;
    accY = a.acceleration.y;
    accZ = a.acceleration.z;
    gyroX = g.gyro.x;
    gyroY = g.gyro.y;
    gyroZ = g.gyro.z;

    return true;
}
