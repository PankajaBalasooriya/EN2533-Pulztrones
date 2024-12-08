#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Wire.h>

class OledDisplay {
private:
    Adafruit_SSD1306 display;   // OLED display object
    uint8_t multiplexerAddress; // I2C address of PCA9548A
    uint8_t oledChannel;        // Channel where OLED is connected

    // Helper method to select the multiplexer channel
    void selectChannel();

public:
    // Constructor
    OledDisplay(uint8_t screenWidth, uint8_t screenHeight, uint8_t muxAddr, uint8_t oledCh);

    // Initialize the display
    bool begin();

    // Display a message on the screen
    void printMessage(const String &message);
};

#endif
