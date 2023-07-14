/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/incubation_routine.h>

#include "HardwareSerial.h"

IncubationRoutine::IncubationRoutine() : curr_time(), motor_controller() {
    curr_state = IDDLE_INCUBATION_STATE;
}

Timer IncubationRoutine::get_curr_time() { return curr_time; }

void IncubationRoutine::before_incubation_state() {
    // 4. Waits untils temperature is set?
    extern float temp_target;
    extern float humd_target;
    temp_target = curr_egg->target_temp;
    humd_target = curr_egg->target_humd;

    motor_controller.set_rotation_interval_hours(curr_egg->eggs_rotation_period);
    motor_controller.set_rotation_duration_seconds(EGG_MOTOR_ROTATION_DURATION);

    // TODO(PedroS): Before starting the incubation, wait for the temperature to settle

    curr_time.start();
    curr_state = IN_INCUBATION_STATE;
}

void IncubationRoutine::in_incubation_state() {
    if (curr_time.get_day() >= curr_egg->incubation_days) {
        curr_state = AFTER_INCUBATION_STATE;
    }

    if (curr_time.get_day() >= curr_egg->start_of_motor_rotation) {
        motor_controller.start_motor_rotation();
    }

    if (curr_time.get_day() >= curr_egg->end_of_motor_rotation) {
        motor_controller.stop_motor_rotation();
    }
}

void IncubationRoutine::after_incubation_state() {
    extern float temp_target;
    extern float humd_target;
    temp_target = 0;
    humd_target = 0;
    curr_state = IDDLE_INCUBATION_STATE;
}

void IncubationRoutine::start_incubation(egg_t *egg) {
    curr_egg = egg;
    curr_state = BEFORE_INCUBATION_STATE;
}
void IncubationRoutine::stop_incubation() { curr_state = AFTER_INCUBATION_STATE; }

egg_t IncubationRoutine::curr_egg_in_incubation() { return *curr_egg; }

bool IncubationRoutine::in_incubation() { return curr_state == IN_INCUBATION_STATE; }

bool IncubationRoutine::routine() {
    motor_controller.routine();
    switch (curr_state) {
        case IDDLE_INCUBATION_STATE:
            break;
        case BEFORE_INCUBATION_STATE:
            before_incubation_state();
            break;
        case IN_INCUBATION_STATE:
            curr_time.update();
            in_incubation_state();
            return true;
        case AFTER_INCUBATION_STATE:
            after_incubation_state();
            break;
        default:
            break;
    }
    return false;
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
