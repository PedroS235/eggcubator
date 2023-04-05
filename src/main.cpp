/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <Arduino.h>
#include <eggcubator/incubation_routine.h>
#include <eggcubator/module/motor_controller.h>
#include <eggcubator/module/thermostat.h>
#include <eggcubator/pins.h>
#include <eggcubator/timer.h>

// --------------------
// - Global Variables -
// --------------------
float temp_target = 0;
float humd_target = 0;
float curr_temp = 0;
float curr_humd = 0;

Thermostat *thermostat;
IncubationRoutine *routine;

void setup() {
    thermostat = new Thermostat();
    routine = new IncubationRoutine();
    Serial.begin(115200);
}

void loop() {
    thermostat->routine(temp_target);
    routine->routine();

    curr_temp = thermostat->get_temp();
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
