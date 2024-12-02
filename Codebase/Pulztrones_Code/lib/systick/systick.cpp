#include "Systick.h"
#include <avr/io.h>


void Systick::begin() {
    // Clear and set timer control registers
    bitClear(TCCR2B, WGM22);
    bitClear(TCCR2A, WGM20);
    bitSet(TCCR2A, WGM21);

    // Set divisor to 128 => 125kHz
    bitSet(TCCR2B, CS22);
    bitClear(TCCR2B, CS21);
    bitSet(TCCR2B, CS20);

    // Set output compare register for 500Hz
    OCR2A = 249;  // (16000000/128/500)-1 => 500Hz

    // Enable timer compare interrupt
    bitSet(TIMSK2, OCIE2A);

    // Short delay to ensure timer runs for a few cycles
    delay(40);
}

void Systick::update() {
    // Grab encoder values first
    encoders.update();
    motion.update();
    // sensors.update();
    

    // Update motor controllers with current motion and sensor feedback
    controller.update_controllers(
        motion.velocity(), 
        motion.omega(),
        sensors.get_steering_feedback()
    );

    // Start ADC conversion cycle
    // adc.start_conversion_cycle();
}

// Create a global instance of Systick
Systick systick;

// update sensor code to work here. 