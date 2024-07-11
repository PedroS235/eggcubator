#include "eggcubator/extras/speaker.h"

Speaker::Speaker(uint8_t pin) { _pin = pin; }

void Speaker::startup_sound() {
    beep(523, 100);
    beep(600, 50);
    beep(700, 100);
    beep(800, 200);
}

void Speaker::button_click_sound() {}

void Speaker::beep(unsigned int frequency, unsigned long duration) {
    tone(_pin, frequency, duration);
}
