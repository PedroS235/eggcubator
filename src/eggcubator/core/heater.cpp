/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "eggcubator/core/heater.h"

#include "eggcubator/config/configuration.h"
#include "eggcubator/config/pins.h"

// TODO: clean heater and make it safer in case thermistor is not connected
// In addition, a watchdog could also be beneficial, where if thetemperature does not
// change something could be wrong

Heater::Heater(float temp_correction_)
    : temp(NAN), temp_target(0), prev_temp_target(0) {
    pid_config = {.kp = PID_TEMP_KP,
                  .ki = PID_TEMP_KI,
                  .kd = PID_TEMP_KD,
                  .min_output = 0,
                  .max_output = 255,
                  .min_integral = 0,
                  .max_integral = 100};

    pid = new PidControl(&pid_config);
    sensor = new Thermistor(PIN_THERMISTOR, 10000);

    temp_correction = temp_correction_;
    pinMode(PIN_HEATER, OUTPUT);
}

float Heater::get_temp() { return temp; }

void Heater::set_temp_correction(float new_correction) {
    temp_correction = new_correction;
}

float Heater::get_temp_correction() { return temp_correction; }

void Heater::set_temp_target(float new_target) { temp_target = new_target; }

void Heater::update_pid_terms(float new_p, float new_i, float new_d) {
    pid_config.kp = new_p;
    pid_config.ki = new_i;
    pid_config.kd = new_d;
    pid->update_pid_config(&pid_config);
}
void Heater::update_pid_terms(pid_config_t new_config) {
    pid_config.kp = new_config.kp;
    pid_config.ki = new_config.ki;
    pid_config.kd = new_config.kd;
    pid_config.min_output = new_config.min_output;
    pid_config.max_output = new_config.max_output;
    pid_config.min_integral = new_config.min_integral;
    pid_config.max_integral = new_config.max_integral;
    pid->update_pid_config(&new_config);
}

pid_config_t Heater::get_pid_terms() { return pid->get_pid_config(); }

bool Heater::run(float temp_target) {
    int ret = sensor->read(&temp);

    if (ret == ESP_FAIL) return false;

    // Reset PID in case the temperature target changes
    if (prev_temp_target != temp_target) {
        pid->reset();
        prev_temp_target = temp_target;
    }
    float heater_pwm = pid->compute(temp_target, temp);

    // Control Heater power using PWM
    analogWrite(PIN_HEATER, heater_pwm);

    return true;
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
