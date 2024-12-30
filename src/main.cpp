/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <Arduino.h>
#include <Wire.h>

#include "eggcubator/config/configuration.h"
#include "eggcubator/core/eeprom_manager.h"
#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"
#include "eggcubator/incubation.h"
#include "eggcubator/server.hpp"
#include "eggcubator/ui/interface.h"
#include "esp32-hal.h"

// -----------------------------------------------------------------------------
// -                             Global Variables                              -
// -----------------------------------------------------------------------------

Heater *heater;
Humidifier *humidifier;
IncubationRoutine *incubation;
Interface *interface;
eggcubator::Server *server;

void heater_task(void *pvParameters) { heater->task(pvParameters); }
void humidifier_task(void *pvParameters) { humidifier->task(pvParameters); }
void incubation_task(void *pvParameters) { incubation->task(pvParameters); }
void interface_task(void *pvParameters) { interface->task(pvParameters); }

void setup() {
    delay(500);
    Wire.begin(UI_I2C_SDA_PIN, UI_I2C_SCK_PIN);
    Serial.begin(115200);

#ifdef DEBUG
    Serial.setDebugOutput(true);
#endif  // DEBUG

    eeprom_setup();

    heater = new Heater();
    humidifier = new Humidifier();
    incubation = new IncubationRoutine(heater, humidifier);
    interface = new Interface(heater, humidifier, incubation);
    server = new eggcubator::Server(heater, humidifier, incubation);

    interface->init();

    log_d("Create Heater Task");
    xTaskCreate(heater_task, "HeaterTask", 5000, NULL, 1, NULL);
    log_d("Create Humidifer Task");
    xTaskCreate(humidifier_task, "HumidifierTask", 5000, NULL, 3, NULL);
    log_d("Create incubation Task");
    xTaskCreate(incubation_task, "RoutineTask", 5000, NULL, 1, NULL);
    log_d("Create Interface Task");
    xTaskCreate(interface_task, "InterfaceTask", 10000, NULL, 2, NULL);

    server->init(WIFI_SSID, WIFI_PW);
}

void loop() {
    // Handled by FreeRTOS tasks.
    // heater->log_stats();
    // humidifier->log_stats();
    // incubation->log_stats();
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    server->handle_client();
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
