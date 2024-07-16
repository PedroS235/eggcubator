/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/incubation.h>

#include "HardwareSerial.h"

IncubationRoutine::IncubationRoutine() : curr_time(), motor_controller() {
    log_v("Setting Incubation state to IDDLE");
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
    motor_controller.set_rotation_duration_seconds(MOTOR_ROTATION_DURATION);

    // TODO(PedroS): Before starting the incubation, wait for the temperature to settle

    curr_time.start();
    log_v("Changing Incubation state: BEFORE state -> IN state");
    curr_state = IN_INCUBATION_STATE;
}

void IncubationRoutine::in_incubation_state() {
    if (curr_time.get_day() >= curr_egg->incubation_days) {
        log_v("Changing Incubation state: IN state -> AFTER state");
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
    log_v("Changing Incubation state: AFTER state -> IDDLE state");
    curr_state = IDDLE_INCUBATION_STATE;
}

void IncubationRoutine::start_incubation(egg_t *egg) {
    curr_egg = egg;
    log_v("Changing Incubation state: START state -> BEFORE state");
    curr_state = BEFORE_INCUBATION_STATE;
}
void IncubationRoutine::stop_incubation() {
    log_v("Changing Incubation state: STOP state -> AFTER state");
    curr_state = AFTER_INCUBATION_STATE;
}

egg_t IncubationRoutine::curr_egg_in_incubation() { return *curr_egg; }

bool IncubationRoutine::in_incubation() { return curr_state == IN_INCUBATION_STATE; }

void IncubationRoutine::task(void *pvParameters) {
    for (;;) {
        log_v("Ticking incubation");
        motor_controller.tick();
        switch (curr_state) {
            case IDDLE_INCUBATION_STATE:
                break;
            case BEFORE_INCUBATION_STATE:
                before_incubation_state();
                break;
            case IN_INCUBATION_STATE:
                curr_time.update();
                in_incubation_state();
                break;
            case AFTER_INCUBATION_STATE:
                after_incubation_state();
                break;
            default:
                break;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
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
