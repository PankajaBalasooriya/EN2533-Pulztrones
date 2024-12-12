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

    navigateMenu(true);
    updateDisplay();
}
void MenuSystem::updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);

    switch (currentState) {
        case MAIN_MENU:
            renderMenu(mainMenuOptions, 4);
            break;
        case TASKS_SUBMENU_PAGE_1:
            renderMenu(tasksSubmenuPage1, 6); // 5 tasks + "Next >"
            break;
        case TASKS_SUBMENU_PAGE_2:
            renderMenu( tasksSubmenuPage2, 6); // 5 tasks + "< Back"
            break;
        case SENSOR_DIAGNOSTICS:
            renderMenu(sensorDiagnosticOptions, 3);
            break;
        case HARDWARE_TESTING:
            renderMenu(hardwareTestingOptions, 4);
            break;
        case SYSTEM_SETTINGS:
            renderMenu(systemSettingsOptions, 4);
            break;
        default:
            display.println("Invalid State");
            break;
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
        case TASKS_SUBMENU_PAGE_1: 
        case TASKS_SUBMENU_PAGE_2:
           menuSize = 6; 
           break;
        case SENSOR_DIAGNOSTICS: menuSize = 3; break;
        case HARDWARE_TESTING: menuSize = 4; break;
        case SYSTEM_SETTINGS: menuSize = 4; break; //continue 
    }

    if (isUpButton) {
        currentSelection = (currentSelection - 1 + menuSize) % menuSize;
    } else {
        currentSelection = (currentSelection + 1) % menuSize;
    }
}

void MenuSystem::selectMenuItem() {
    switch (currentState) {
        case MAIN_MENU:
            if (currentSelection == 4) return; // "Back" option, do nothing
            currentState = static_cast<MenuState>(currentSelection + 1); // Transition to selected submenu
            currentSelection = 0;
            break;

        case TASKS_SUBMENU_PAGE_1:
            if (currentSelection == 5) { // "Next >" option
                currentState = TASKS_SUBMENU_PAGE_2;
                currentSelection = 0;
            } else if (currentSelection == 4) { // "< Back" option
                currentState = MAIN_MENU;
                currentSelection = 0;
            } else if(currentSelection==0) {
               start_square(); // Execute task from Page 1
            }
            else if(currentSelection==1) {
               bar_code(); // Execute task from Page 1
            }
             else if(currentSelection==2) {
                execute_MoveToMaze();
             }
            else if(currentSelection==3) {
               execute_maze();
            }
            break;

        case TASKS_SUBMENU_PAGE_2:
            if (currentSelection == 5) { // "< Back" option
                currentState = TASKS_SUBMENU_PAGE_1;
                currentSelection = 0;
            } else if (currentSelection == 0) { // "< Back" to MAIN_MENU
               executeDashedLine();
            } 
            else if (currentSelection==1){
                executePortalNavigation();
            }
            else if(currentSelection==2){
                executeBoxArranging();
            }
            else if (currentSelection==3){
                executeChamberInsertion();
            }
            else if (currentSelection==4){
                executeHiddenTask();
            }
            break;

    //     case SENSOR_DIAGNOSTICS:
    //         if (currentSelection == 2) { // "< Back"
    //             currentState = MAIN_MENU;
    //             currentSelection = 0;
    //         } else {
    //             executeDiagnostic(currentSelection); // Run diagnostics
    //         }
    //         break;

    //     case HARDWARE_TESTING:
    //         if (currentSelection == 3) { // "< Back"
    //             currentState = MAIN_MENU;
    //             currentSelection = 0;
    //         } else {
    //             executeHardwareTest(currentSelection); // Run hardware test
    //         }
    //         break;

    //     case SYSTEM_SETTINGS:
    //         if (currentSelection == 3) { // "< Back"
    //             currentState = MAIN_MENU;
    //             currentSelection = 0;
    //         } else {
    //             updateSetting(currentSelection); // Update system settings
    //         }
    //         break;

        default:
            currentState = MAIN_MENU;
            currentSelection = 0;
            break;
    
    }
    currentSelection=0;
    //updateDisplay();
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

void MenuSystem::start_square() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Start Square");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem ::  bar_code(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Barcode running");
    display.display();
    delay(2000); // Placeholder for task execution
}

void MenuSystem :: execute_MoveToMaze(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Moving to Maze");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem :: execute_maze(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Solving Maze");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem :: executeColorLine(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Color line");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem :: executeDashedLine(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Dashed line");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem :: executePortalNavigation(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Portal Navigation");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem :: executeBoxArranging(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Box Arranging");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem ::  executeChamberInsertion(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Chamber insertion");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem ::  executeHiddenTask(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Hidden Task");
    display.display();
    delay(2000); // Placeholder for task execution
}
void MenuSystem ::  executeUnevenTerrain(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Uneven Terrain");
    display.display();
    delay(2000); // Placeholder for task execution
}