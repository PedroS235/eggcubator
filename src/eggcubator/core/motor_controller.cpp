/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/config/pins.h>
#include <eggcubator/core/motor_controller.h>
#include <eggcubator/extras/time_conversions.h>

MotorController::MotorController() {
    pinMode(PIN_MOTOR, OUTPUT);
    curr_state = IDDLE_MOTOR_STATE;
}

void MotorController::start_motor_rotation() {
    prev_rotation = millis();
    trigger_timer = millis();
    curr_state = WAITING_MOTOR_STATE;
}

void MotorController::stop_motor_rotation() { curr_state = IDDLE_MOTOR_STATE; }

void MotorController::set_rotation_interval_hours(unsigned long interval) {
    rotation_interval = hour_to_millis(interval);
}

void MotorController::set_rotation_interval_seconds(unsigned long interval) {
    rotation_interval = sec_to_millis(interval);
}

void MotorController::set_rotation_duration_hours(unsigned long interval) {
    rotation_duration = hour_to_millis(interval);
}

void MotorController::set_rotation_duration_seconds(unsigned long interval) {
    rotation_duration = sec_to_millis(interval);
}

void MotorController::waiting_state() {
    unsigned long now = millis();
    if (now - prev_rotation >= rotation_interval) {
        digitalWrite(PIN_MOTOR, HIGH);
        curr_state = ROTATING_MOTOR_STATE;
        prev_rotation = now;
        start_of_rotation = now;
    }
}

void MotorController::rotating_state() {
    unsigned long now = millis();
    if (now - start_of_rotation >= rotation_duration) {
        digitalWrite(PIN_MOTOR, LOW);
        curr_state = WAITING_MOTOR_STATE;
    }
}

void MotorController::routine() {
    switch (curr_state) {
        case IDDLE_MOTOR_STATE:
            break;
        case ROTATING_MOTOR_STATE:
            rotating_state();
            break;
        case WAITING_MOTOR_STATE:
            waiting_state();
            break;
        default:
            break;
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
