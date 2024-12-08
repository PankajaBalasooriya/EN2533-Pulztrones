#include "OledDisplay.h"

// Constructor
OledDisplay::OledDisplay(uint8_t screenWidth, uint8_t screenHeight, uint8_t muxAddr, uint8_t oledCh)
    : display(screenWidth, screenHeight, &Wire, -1), multiplexerAddress(muxAddr), oledChannel(oledCh) {}

// Helper method to select the multiplexer channel
void OledDisplay::selectChannel() {
    Wire.beginTransmission(multiplexerAddress);
    Wire.write(1 << oledChannel); // Select the OLED channel
    Wire.endTransmission();
}

// Initialize the display
bool OledDisplay::begin() {
    selectChannel(); // Activate the OLED channel
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Use the correct OLED I2C address
        return false; // Return false if initialization fails
    }
    display.clearDisplay();
    display.display();
    return true;
}

// Display a message on the screen
void OledDisplay::printMessage(const String &message) {
    selectChannel(); // Ensure the OLED channel is active
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(message);
    display.display();
}
