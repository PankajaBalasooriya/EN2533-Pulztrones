#ifndef BLUETOOTH_DEBUG_H
#define BLUETOOTH_DEBUG_H

#include <Arduino.h>

void initBluetoothDebug(long baudRate = 9600);
void sendBluetoothData(String data);
void logToMonitor(String data);

#endif
