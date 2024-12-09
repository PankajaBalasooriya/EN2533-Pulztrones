#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum MenuState {
    MAIN_MENU,
    TASKS_SUBMENU,
    SENSOR_DIAGNOSTICS,
    HARDWARE_TESTING,
    SYSTEM_SETTINGS,
    
    TASK_LINE_FOLLOWING,
    TASK_OBSTACLE_AVOIDANCE,
    TASK_PAYLOAD_PICKUP,
    TASK_FREE_EXPLORATION,
    
    DIAG_MPU6050,
    DIAG_TOF_SENSORS,
    
    TEST_SERVOS,
    TEST_MOTORS,
    TEST_BUTTONS_LEDS
};

class MenuSystem {
private:
    Adafruit_SSD1306 display;
    MenuState currentState;
    int currentSelection;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay;

    const char* mainMenuOptions[5] = {
        "Tasks", "Sensor Diagnostics", "Hardware Testing", 
        "System Settings", "< Back"
    };

    const char* tasksSubmenuOptions[5] = {
        "Line Following", "Obstacle Avoidance", 
        "Payload Pickup", "Free Exploration", "< Back"
    };

    const char* sensorDiagnosticOptions[3] = {
        "MPU6050 Gyroscope", "VL53L0X ToF Sensors", "< Back"
    };

    const char* hardwareTestingOptions[4] = {
        "Servo Motors", "Motors and Wheels", "Buttons and LEDs", "< Back"
    };

    const char* systemSettingsOptions[4] = {
        "Task Parameters", "Sensor Calibration", 
        "Screen Brightness", "< Back"
    };

    void renderMenu(const char** options, int optionCount);
    void executeLineFollowing();
    void executeObstacleAvoidance();
    void executePayloadPickup();
    void executeFreeExploration();

public:
    MenuSystem(uint8_t screenWidth, uint8_t screenHeight, uint8_t oledReset, uint8_t oledAddr);
    void begin();
    void updateDisplay();
    void navigateMenu(bool isUpButton);
    void selectMenuItem();
    void handleInput(int buttonUp, int buttonNext, int buttonSelect);
};

#endif // MENUSYSTEM_H
