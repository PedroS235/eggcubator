/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/incubation.h>

const char *state_to_string(incubation_state_e state) {
    switch (state) {
        case IDDLE_INCUBATION_STATE:
            return "IDDLE_INCUBATION";
        case BEFORE_INCUBATION_STATE:
            return "BEFORE_INCUBATION";
        case IN_INCUBATION_STATE:
            return "IN_INCUBATION";
        case AFTER_INCUBATION_STATE:
            return "AFTER_INCUBATION";
        default:
            return "UNKNOWN_STATE";
    }
}

IncubationRoutine::IncubationRoutine(Heater *heater, Humidifier *humidifier)
    : curr_time(), motor_controller(), _heater(heater), _humidifier(humidifier) {
    log_d("Setting Incubation state to IDDLE");
    curr_state = IDDLE_INCUBATION_STATE;
}

Timer IncubationRoutine::get_curr_time() { return curr_time; }

void IncubationRoutine::before_incubation_state() {
    _heater->set_temp_target(curr_egg.target_temp);
    _humidifier->set_humidity_target(curr_egg.target_humd);

    motor_controller.set_rotation_interval_hours(curr_egg.eggs_rotation_period);

    // TODO(PedroS): Before starting the incubation, wait for the temperature to settle

    curr_time.start();
    log_d("Changing Incubation state: BEFORE state -> IN state");
    curr_state = IN_INCUBATION_STATE;
}

void IncubationRoutine::in_incubation_state() {
    if (curr_time.get_day() >= curr_egg.incubation_days) {
        log_d("Changing Incubation state: IN state -> AFTER state");
        curr_state = AFTER_INCUBATION_STATE;
    }

    if (curr_time.get_day() >= curr_egg.start_of_motor_rotation) {
        motor_controller.start_motor_rotation();
    }

    if (curr_time.get_day() >= curr_egg.end_of_motor_rotation) {
        motor_controller.stop_motor_rotation();
    }
}

void IncubationRoutine::after_incubation_state() {
    _heater->turn_off();
    // close vent

    log_d("Changing Incubation state: AFTER state -> IDDLE state");
    curr_state = IDDLE_INCUBATION_STATE;
}

void IncubationRoutine::start_incubation(egg_t egg) {
    curr_egg = egg;
    log_d("Changing Incubation state: START state -> BEFORE state");
    curr_state = BEFORE_INCUBATION_STATE;
}
void IncubationRoutine::stop_incubation() {
    log_d("Changing Incubation state: STOP state -> AFTER state");
    curr_state = AFTER_INCUBATION_STATE;
}

egg_t IncubationRoutine::curr_egg_in_incubation() { return curr_egg; }

bool IncubationRoutine::in_incubation() { return curr_state == IN_INCUBATION_STATE; }

void IncubationRoutine::log_stats() {
    log_i("Incubation: State: %s", state_to_string(curr_state));
}

void IncubationRoutine::set_temperature(float temp) { _heater->set_temp_target(temp); }
void IncubationRoutine::set_humidity(float humd) {
    _humidifier->set_humidity_target(humd);
}

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

void IncubationRoutine::set_motor_rotation(unsigned long duration) {
    motor_controller.set_rotation_duration_seconds(duration);
}

unsigned long IncubationRoutine::get_motor_rotation() {
    return motor_controller.get_rotation_duration();
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
