/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#include "eggcubator/extras/pid_control.h"

#include "esp32-hal-log.h"

PidControl::PidControl(pid_config_t *config) : _error_sum(0), _prev_error(0) {
    _config = config;
}

void PidControl::update_pid_config(pid_config_t *config) { _config = config; }

pid_config_t PidControl::get_pid_config() { return *_config; }

void PidControl::reset() {
    _error_sum = 0;
    _prev_error = 0;
}

float PidControl::compute(float setpoint, float current_value) {
    const float error = setpoint - current_value;

    // Eliminate possible noise on the integral term.
    if (error == 0 && setpoint == 0) {
        reset();
    }

    // Compute P term
    const float p = _config->kp * error;

    // Compute I term
    float i = _config->ki * _error_sum;
    i = MIN(MAX(i, _config->min_integral), _config->max_integral);
    i = MAX(MIN(i, _config->max_integral), _config->min_integral);

    // Compute D term
    const float d = _config->kd * (error - _prev_error);

    float correction = p + i + d;

    _prev_error = error;
    _error_sum += error;

    correction = MIN(MAX(i, _config->min_output), _config->max_output);
    correction = MAX(MIN(i, _config->max_output), _config->min_output);

    return correction;
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
