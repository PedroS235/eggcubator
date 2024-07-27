/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef HEATER_H
#define HEATER_H

#include "eggcubator/drivers/thermistor.h"
#include "eggcubator/extras/pid_control.h"

/**
 * @brief Controlls the temperature of a chamber to a desired target
 * temperature, by controlling an heater with a PWM signal
 */
class Heater {
   private:
    float temp;
    int curr_power;
    float temp_correction;
    float temp_target;
    float prev_temp_target;
    uint8_t _pin;

    pid_config_t pid_config;
    PidControl* pid;
    Thermistor* sensor;

   private:
    void _set_duty(uint8_t duty);

   public:
    /**
     * @brief Constructor of the class Heater
     *
     * @param temp_reading_interval_ is the interval at wich a new temperature
     * reading is made
     * @param temp_correction_ is a correction that will be applied to the
     * temperature reading to calibrate the sensor
     */
    Heater(float temp_correction_ = 0);

    /**
     * @brief Method to return the current temperature reading
     *
     * @returns Last temperature reading
     */
    float get_temp();
    float get_target();

    /**
     * @brief Method to update the current temperature correction
     *
     * @param new_correction is the new correction value to be applied
     */
    void set_temp_correction(float new_correction);
    float get_temp_correction();

    /**
     * @brief Method to set the current temperature target the heater
     * should aim for
     *
     * @param new_target is the new temperature target that should be applied
     *
     */
    void set_temp_target(float new_target);
    void turn_off();

    /**
     * @brief Updates the current PID term values of the PID controller
     *
     * @param new_p is the new proportional term to be set
     * @param new_i is the new integral term to be set
     * @param new_d is the new derivative term to be set
     */
    void update_pid_terms(float new_p, float new_i, float new_d);
    void update_pid_terms(pid_config_t new_terms);
    void update_pid_kp(float new_p);
    void update_pid_ki(float new_i);
    void update_pid_kd(float new_d);
    pid_config_t get_pid_terms();

    void log_stats();

    /**
     * @brief Main method that should run continuously.
     * It is responsible of reading the temperature and controlling the heating
     * source in order to maintain the targeted temperature
     *
     * @param temp_target is the targeted temperature that the heater should
     * aim for
     *
     * @return True if temperature sensor is working as expected, false otherwise
     */
    void task(void* pvParameters);
};

#endif  // !HEATER_H

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
