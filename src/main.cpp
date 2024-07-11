/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <Arduino.h>
#include <Wire.h>

#include "FreeRTOS.h"
#include "eggcubator/config/configuration.h"
#include "eggcubator/config/pins.h"
#include "eggcubator/core/eeprom_manager.h"
#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"
#include "eggcubator/egg.h"
#include "eggcubator/extras/speaker.h"
#include "eggcubator/incubation.h"
#include "eggcubator/ui/display_manager.h"
#include "eggcubator/ui/eggcubator_ui.h"

// -----------------------------------------------------------------------------
// -                             Global Variables                              -
// -----------------------------------------------------------------------------
float temp_target = 0;
float humd_target = 0;
float curr_temp = 0;
float curr_humd = 0;
egg_t selected_egg;

Heater *heater;
Humidifier *humidifier;
IncubationRoutine *routine;
EggCubatorUI *ui;
DisplayManager *display;
Speaker *speaker;

void HeaterTask(void *pvParameters) {
    for (;;) {
        heater->run(temp_target);
        curr_temp = heater->get_temp();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void HumidifierTask(void *pvParameters) {
    for (;;) {
        humidifier->routine(humd_target);
        curr_humd = humidifier->get_humidity();
        // NOTE: The dht sensor only update every 2 seconds.
        // Thus, running the humidifier every 2 seconcs should be enough.
        // This needs to be checked if he pid does not get affected
        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Adjust the delay as needed
    }
}

void IncubationTask(void *pvParameters) {
    for (;;) {
        routine->routine();
        // NOTE: The incubation should work fine with seconds precision
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void UiTask(void *pvParameters) {
    for (;;) {
        ui->render();
        vTaskDelay(SCREEN_REFRESH_RATE / portTICK_PERIOD_MS);
    }
}

void setup() {
    delay(500);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCK);  // Define which pins are to be used for i2c
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    eeprom_setup();

    speaker = new Speaker(PIN_BUZZER);
    heater = new Heater();
    humidifier = new Humidifier();
    routine = new IncubationRoutine();
    ui = new EggCubatorUI();
    display = new DisplayManager();

    display->draw_boot_screen("EGGCUBATOR");
    delay(BOOTSCREEN_DURATION);
    // eeprom_reset();

    speaker->startup_sound();

    xTaskCreate(HeaterTask, "HeaterTask", 5000, NULL, 1, NULL);
    xTaskCreate(HumidifierTask, "HumidifierTask", 5000, NULL, 3, NULL);
    xTaskCreate(IncubationTask, "RoutineTask", 5000, NULL, 1, NULL);
    xTaskCreate(UiTask, "ScreenTask", 10000, NULL, 2, NULL);
}

void loop() {
    // Handled by FreeRTOS tasks.
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
