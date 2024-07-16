/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "eggcubator/core/heater.h"

#include "eggcubator/config/configuration.h"

Heater::Heater(uint8_t pin, float temp_correction_)
    : temp(NAN), temp_target(0), prev_temp_target(0), _pin(pin) {
    pid_config = {.kp = HEATER_PID_KP,
                  .ki = HEATER_PID_KI,
                  .kd = HEATER_PID_KD,
                  .min_output = 0,
                  .max_output = 255,
                  .min_integral = 0,
                  .max_integral = 100};

    pid = new PidControl(&pid_config);
    sensor = new Thermistor(HEATER_SENSOR_PIN, 10000);

    temp_correction = temp_correction_;
    pinMode(_pin, OUTPUT);
}

float Heater::get_temp() { return temp; }

void Heater::set_temp_correction(float new_correction) {
    log_v("Setting new temperature correction from %f to %f",
          temp_correction,
          new_correction);
    temp_correction = new_correction;
}

float Heater::get_temp_correction() { return temp_correction; }

void Heater::set_temp_target(float new_target) {
    log_v("Setting new temperature target from %f to %f", temp_target, new_target);
    temp_target = new_target;
}

void Heater::update_pid_terms(float new_p, float new_i, float new_d) {
    log_v(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        pid_config.kp,
        pid_config.ki,
        pid_config.kd,
        new_p,
        new_i,
        new_d);

    pid_config.kp = new_p;
    pid_config.ki = new_i;
    pid_config.kd = new_d;
    pid->update_pid_config(&pid_config);
}
void Heater::update_pid_terms(pid_config_t new_config) {
    log_v(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        pid_config.kp,
        pid_config.ki,
        pid_config.kd,
        new_config.kp,
        new_config.ki,
        new_config.kd);

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

void Heater::_set_duty(uint8_t duty) { analogWrite(_pin, duty); }

void Heater::task(void* pvParameters) {
    for (;;) {
        // TODO: use set_temp_target instead of passing as a parameter to tick()
        log_v("Ticking heater");
        int ret = sensor->read(&temp);

        if (ret == ESP_FAIL) {
            log_e("Thermistor reading not valid. Shutting down heater for safety.");
            _set_duty(0);
        }

        log_v("Temperature Reading %f", temp);

        if (temp > HEATER_MAX_TEMP || temp < HEATER_MIN_TEMP) {
            log_w(
                "Temperature is not within allowed range. Shutting down heater "
                "for safety.");
            _set_duty(0);
        }

        // Reset PID in case the temperature target changes
        if (prev_temp_target != temp_target) {
            pid->reset();
            prev_temp_target = temp_target;
        }
        float heater_pwm = pid->compute(temp_target, temp);

        // Control Heater power using PWM
        _set_duty(heater_pwm);

        vTaskDelay(100 / portTICK_PERIOD_MS);
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
