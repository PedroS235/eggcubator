/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/config/configuration.h>
#include <eggcubator/core/motor_controller.h>
#include <eggcubator/extras/time_conversions.h>

#include "AccelStepper.h"

MotorController::MotorController()
    : stepper(AccelStepper::FULL4WIRE, MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4) {
    log_d("Setting MotorController state to IDDLE");
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(100);
    curr_state = IDDLE_MOTOR_STATE;
    set_rotation_duration_seconds(MOTOR_ROTATION_DURATION);
}

void MotorController::start_motor_rotation() {
    unsigned long now = millis();
    stepper.setSpeed(60);
    log_d("Changing MotorController state: WAITING state -> ROTATING state");
    curr_state = ROTATING_MOTOR_STATE;
    prev_rotation = now;
    start_of_rotation = now;
}

void MotorController::stop_motor_rotation() {
    log_d("Changing MotorController state: STOP state -> IDDLE state");
    curr_state = IDDLE_MOTOR_STATE;
}

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
        stepper.setSpeed(200);
        log_d("Changing MotorController state: WAITING state -> ROTATING state");
        curr_state = ROTATING_MOTOR_STATE;
        prev_rotation = now;
        start_of_rotation = now;
    }
}

void MotorController::rotating_state() {
    unsigned long now = millis();
    if (now - start_of_rotation >= rotation_duration) {
        stepper.setSpeed(0);
        stepper.stop();
        stepper.disableOutputs();
        log_d("Changing MotorController state: ROTATING state -> WAITING state");
        curr_state = WAITING_MOTOR_STATE;
    }
}

void MotorController::tick() {
    log_v("Ticking motor controller");
    stepper.runSpeed();
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

unsigned long MotorController::get_rotation_duration() {
    return millis_to_seconds(rotation_duration);
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
