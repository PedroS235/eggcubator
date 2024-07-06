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

Heater::Heater(unsigned long temp_reading_interval_, float temp_correction_)
    : temp(NAN), temp_target(0), prev_temp_target(0), last_temp_reading_time(0) {
    pid = new PID(PID_TEMP_KP, PID_TEMP_KI, PID_TEMP_KD);
    sensor = new Thermistor(PIN_THERMISTOR, 10000);

    temp_reading_interval = temp_reading_interval_;
    temp_correction = temp_correction_;
    pinMode(PIN_HEATER, OUTPUT);
}

void Heater::update_temp() {
    unsigned long now = millis();
    if (now - last_temp_reading_time >= temp_reading_interval) {
        // TODO: if sesor reading is very low, -273.15, it means that the th is not
        // connected
        const float reading = sensor->read();
        if (!isnan(reading)) {
            temp = reading + temp_correction;
        } else {
            temp = NAN;
        }
        last_temp_reading_time = now;
    }
}

float Heater::get_temp() { return temp; }

void Heater::set_temp_correction(float new_correction) {
    temp_correction = new_correction;
}

float Heater::get_temp_correction() { return temp_correction; }

void Heater::set_temp_target(float new_target) { temp_target = new_target; }

void Heater::update_pid_p_term(float new_p) { pid->update_p_term(new_p); }

void Heater::update_pid_i_term(float new_i) { pid->update_i_term(new_i); }

void Heater::update_pid_d_term(float new_d) { pid->update_d_term(new_d); }

void Heater::update_pid_terms(float new_p, float new_i, float new_d) {
    pid->update_pid_terms(new_p, new_i, new_d);
}
void Heater::update_pid_terms(pid_terms_t new_pid_terms) {
    pid->update_pid_terms(new_pid_terms);
}

pid_terms_t Heater::get_pid_terms() { return pid->get_pid_terms(); }

bool Heater::run(float temp_target) {
    update_temp();

    if (isnan(temp)) {
        return false;
    }

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
