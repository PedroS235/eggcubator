/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "module/pid.h"

PID::PID(float kp_, float ki_, float kd_) : error_sum(0), prev_error(0) {
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

void PID::update_p_term(float new_p) { kp = new_p; }

void PID::update_i_term(float new_i) { ki = new_i; }

void PID::update_d_term(float new_d) { kd = new_d; }

void PID::update_pid_terms(float new_p, float new_i, float new_d) {
    kp = new_p;
    ki = new_i;
    kd = new_d;
}

void PID::reset() {
    error_sum = 0;
    prev_error = 0;
}

float PID::compute(float setpoint, float current_value) {
    const float error = setpoint - current_value;
    error_sum += error;

    // Compute P term
    const float p = kp * error;

    // Compute I term
    const float i = ki * error_sum;

    // Compute D term
    const float d = kd * (error - prev_error);

    prev_error = error;

    float correction = p + i + d;

    if (correction >= 0 && correction <= 255) {
        return correction;
    } else {
        return correction < 0 ? 0 : 255;
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
