#include <eggcubator/gui/eggcubator_ui.h>

#include "Arduino.h"
#include "eggcubator/pins.h"
#include "eggcubator/utils/rotary_encoder.h"

EggCubatorUI::EggCubatorUI(RotaryEncoder *encoder_) : display() {
    encoder = encoder_;
    pinMode(PIN_ENCODER_SW, INPUT_PULLUP);
    encoder_pos = encoder->getPosition();
    prev_encoder_pos = encoder_pos;
    button_pressed = false;
}

void EggCubatorUI::encoder_update() {
    encoder_pos = encoder->getPosition();
    if (encoder_pos != prev_encoder_pos) {
        Serial.print("Position: ");
        Serial.println(encoder_pos);
    }
    prev_encoder_pos = encoder_pos;

    if (digitalRead(PIN_ENCODER_SW) == LOW) {
        if (millis() - last_button_press > 50) {
            button_pressed = true;
            Serial.println("Button pressed!");
        }
        last_button_press = millis();
    } else {
        button_pressed = false;
    }
}

void EggCubatorUI::render() {
    encoder_update();
    display.draw_number_change("Test", encoder_pos);
}
