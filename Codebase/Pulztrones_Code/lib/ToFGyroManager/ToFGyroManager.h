#ifndef TOF_GYRO_MANAGER_H
#define TOF_GYRO_MANAGER_H

#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Maximum number of ToF sensors
#define MAX_TOF_SENSORS 3

class ToFGyroManager {
public:
    ToFGyroManager(uint8_t pca9548aAddress = 0x70);
    
    // Initialization methods
    bool begin();
    bool initializeToFSensors();
    bool initializeGyro();

    // Data retrieval methods
    uint16_t getToFDistance(uint8_t sensorIndex);
    bool isToFOutOfRange(uint8_t sensorIndex);
    bool getGyroData(float &accX, float &accY, float &accZ, float &gyroX, float &gyroY, float &gyroZ);

private:
    // Helper methods
    void selectChannel(uint8_t channel);

    // Members
    uint8_t pca9548aAddress;
    VL53L0X tofSensors[MAX_TOF_SENSORS];
    Adafruit_MPU6050 mpu;
    bool tofInitialized[MAX_TOF_SENSORS];
};

#endif // TOF_GYRO_MANAGER_H
