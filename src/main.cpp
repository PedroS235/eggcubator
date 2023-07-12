/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <Arduino.h>

#include "RotaryEncoder.h"
#include "eggcubator/configuration.h"
#include "eggcubator/egg.h"
#include "eggcubator/gui/display_manager.h"
#include "eggcubator/gui/eggcubator_ui.h"
#include "eggcubator/incubation_routine.h"
#include "eggcubator/module/eeprom_manager.h"
#include "eggcubator/module/motor_controller.h"
#include "eggcubator/module/pid.h"
#include "eggcubator/module/thermostat.h"
#include "eggcubator/pins.h"

// -----------------------------------------------------------------------------
// -                             Global Variables                              -
// -----------------------------------------------------------------------------
float temp_target = 0;
float humd_target = 0;
float curr_temp = 0;
float curr_humd = 0;
egg_t selected_egg;
unsigned long prev_screen_refresh;

Thermostat *thermostat;
IncubationRoutine *routine;
RotaryEncoder *encoder;
EggCubatorUI *ui;
DisplayManager *display;

// -----------------------------------------------------------------------------
// -                            Helper Functions                               -
// -----------------------------------------------------------------------------

void encoder_ISR() { encoder->tick(); }

void setup_constructers() {
    thermostat = new Thermostat();
    routine = new IncubationRoutine();
    encoder = new RotaryEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT);
    ui = new EggCubatorUI(encoder);
    display = new DisplayManager();
}

void setup_interrupts() {
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_CLK), encoder_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_DT), encoder_ISR, CHANGE);
}

void startup_sound() {
    tone(PIN_BUZZER, 523, 100);
    tone(PIN_BUZZER, 600, 50);
    tone(PIN_BUZZER, 700, 100);
    tone(PIN_BUZZER, 800, 200);
}

void setup() {
    delay(500);
    Serial.begin(115200);
    eeprom_setup();

    setup_constructers();
    setup_interrupts();
    display->draw_boot_screen("EGGCUBATOR");
    delay(BOOTSCREEN_DURATION);
    /* eeprom_reset(); */

    startup_sound();
}

void loop() {
    thermostat->routine(temp_target);
    routine->routine();
    curr_temp = thermostat->get_temp();
    if (millis() - prev_screen_refresh > 2) {
        ui->render();
        prev_screen_refresh = millis();
    }
}

/*
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
