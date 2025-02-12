/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "eggcubator/core/heater.h"

#include "eggcubator/config/configuration.h"
#include "esp32-hal-log.h"

Heater::Heater(float temp_correction)
    : _temp(NAN),
      _curr_power(0),
      _temp_correction(temp_correction),
      _temp_target(0),
      _prev_temp_target(0),
      _pin(HEATER_PIN) {
    _pid_config = {.kp = HEATER_PID_KP,
                   .ki = HEATER_PID_KI,
                   .kd = HEATER_PID_KD,
                   .min_output = 0,
                   .max_output = 255,
                   .min_integral = 0,
                   .max_integral = 150};

    _pid = new PidControl(&_pid_config, HEATER_CONTROL_TYPE);
    _sensor = new Thermistor(HEATER_SENSOR_PIN, 10000);

    pinMode(_pin, OUTPUT);
}

float Heater::get_temp() { return _temp; }
float Heater::get_target() { return _temp_target; }

void Heater::set_temp_correction(float new_correction) {
    log_v("Setting new temperature correction from %f to %f",
          temp_correction,
          new_correction);
    _temp_correction = new_correction;
}

float Heater::get_temp_correction() { return _temp_correction; }

void Heater::set_temp_target(float new_target) {
    log_v("Setting new temperature target from %f to %f", temp_target, new_target);
    _temp_target = new_target;
}

int Heater::get_curr_power() { return _curr_power; }

void Heater::turn_off() { _temp_target = 0; }

void Heater::update_pid_terms(float new_p, float new_i, float new_d) {
    log_i(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        _pid_config.kp,
        _pid_config.ki,
        _pid_config.kd,
        new_p,
        new_i,
        new_d);

    _pid_config.kp = new_p;
    _pid_config.ki = new_i;
    _pid_config.kd = new_d;
    _pid->update_pid_config(&_pid_config);
}
void Heater::update_pid_terms(pid_config_t new_config) {
    log_i(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        _pid_config.kp,
        _pid_config.ki,
        _pid_config.kd,
        new_config.kp,
        new_config.ki,
        new_config.kd);

    _pid_config.kp = new_config.kp;
    _pid_config.ki = new_config.ki;
    _pid_config.kd = new_config.kd;
    _pid_config.min_output = new_config.min_output;
    _pid_config.max_output = new_config.max_output;
    _pid_config.min_integral = new_config.min_integral;
    _pid_config.max_integral = new_config.max_integral;
    _pid->update_pid_config(&new_config);
}

void Heater::update_pid_kp(float new_p) {
    _pid_config.kp = new_p;
    _pid->update_pid_config(&_pid_config);
}
void Heater::update_pid_ki(float new_i) {
    _pid_config.ki = new_i;
    _pid->update_pid_config(&_pid_config);
}
void Heater::update_pid_kd(float new_d) {
    _pid_config.kd = new_d;
    _pid->update_pid_config(&_pid_config);
}

pid_config_t Heater::get_pid_terms() { return _pid->get_pid_config(); }

void Heater::_set_duty(uint8_t duty) { analogWrite(_pin, duty); }

void Heater::log_stats() {
    log_i("Heater: %f/%f°C | Power: %d", _temp, _temp_target, _curr_power);
}

void Heater::task(void* pvParameters) {
    for (;;) {
        vTaskDelay(250 / portTICK_PERIOD_MS);
        int ret = _sensor->read(&_temp);

        if (ret == ESP_FAIL) {
            log_e("Thermistor reading not valid. Shutting down heater for safety.");
            _set_duty(0);
            continue;
        }

        // Apply temperature correction
        _temp += _temp_correction;

        log_v("Temperature Reading %f", temp);

        if (_temp >= HEATER_MAX_TEMP || _temp <= HEATER_MIN_TEMP) {
            log_w(
                "Temperature is not within allowed range. Shutting down heater "
                "for safety.");
            _set_duty(0);
            continue;
        }

        // Reset PID in case the temperature target changes
        if (_prev_temp_target != _temp_target) {
            _pid->reset();
            _prev_temp_target = _temp_target;
        }
        _curr_power = _pid->compute(_temp_target, _temp);

        // Control Heater power using PWM
        _set_duty(_curr_power);
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
