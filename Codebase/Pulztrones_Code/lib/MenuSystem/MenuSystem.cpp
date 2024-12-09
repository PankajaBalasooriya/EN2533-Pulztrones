#include "MenuSystem.h"

MenuSystem::MenuSystem(uint8_t screenWidth, uint8_t screenHeight, uint8_t oledReset, uint8_t oledAddr) :
    display(screenWidth, screenHeight, &Wire, oledReset),
    currentState(MAIN_MENU),
    currentSelection(0),
    lastDebounceTime(0),
    debounceDelay(50) {}

void MenuSystem::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (1); // Handle OLED initialization failure
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.display();
}

void MenuSystem::updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);

    switch (currentState) {
        case MAIN_MENU: renderMenu(mainMenuOptions, 5); break;
        case TASKS_SUBMENU: renderMenu(tasksSubmenuOptions, 5); break;
        case SENSOR_DIAGNOSTICS: renderMenu(sensorDiagnosticOptions, 3); break;
        case HARDWARE_TESTING: renderMenu(hardwareTestingOptions, 4); break;
        case SYSTEM_SETTINGS: renderMenu(systemSettingsOptions, 4); break;
        default: display.println("Not Implemented"); break;
    }

    display.display();
}

void MenuSystem::renderMenu(const char** options, int optionCount) {
    for (int i = 0; i < optionCount; i++) {
        if (i == currentSelection) {
            display.setTextColor(BLACK, WHITE);  // Highlight selection
        } else {
            display.setTextColor(WHITE);
        }
        display.println(options[i]);
    }
}

void MenuSystem::navigateMenu(bool isUpButton) {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime) < debounceDelay) return; // Debounce
    lastDebounceTime = currentTime;

    int menuSize = 5;  // Default to main menu size
    switch (currentState) {
        case MAIN_MENU: menuSize = 5; break;
        case TASKS_SUBMENU: menuSize = 5; break;
        case SENSOR_DIAGNOSTICS: menuSize = 3; break;
        case HARDWARE_TESTING: menuSize = 4; break;
        case SYSTEM_SETTINGS: menuSize = 4; break;
    }

    if (isUpButton) {
        currentSelection = (currentSelection - 1 + menuSize) % menuSize;
    } else {
        currentSelection = (currentSelection + 1) % menuSize;
    }
}

void MenuSystem::selectMenuItem() {
    if (currentState == MAIN_MENU && currentSelection == 4) return; // Handle Back

    switch (currentState) {
        case MAIN_MENU:
            currentState = static_cast<MenuState>(currentSelection + 1);
            currentSelection = 0;
            break;
        case TASKS_SUBMENU:
            if (currentSelection == 4) currentState = MAIN_MENU;
            else if (currentSelection == 0) executeLineFollowing();
            break;
        default: currentState = MAIN_MENU; break;
    }
    currentSelection = 0;
}

void MenuSystem::handleInput(int buttonUp, int buttonNext, int buttonSelect) {
    if (digitalRead(buttonUp) == HIGH) {
        navigateMenu(true);
        updateDisplay();
        delay(200);
    }
    if (digitalRead(buttonNext) == HIGH) {
        navigateMenu(false);
        updateDisplay();
        delay(200);
    }
    if (digitalRead(buttonSelect) == HIGH) {
        selectMenuItem();
        updateDisplay();
        delay(200);
    }
}

void MenuSystem::executeLineFollowing() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Line Following Task");
    display.display();
    delay(2000); // Placeholder for task execution
}
