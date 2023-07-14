/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <DHT.h>

#include "eggcubator/configuration.h"
#include "eggcubator/module/pid.h"

/**
 * @brief Controlls the temperature of a chamber to a desired target
 * temperature, by controlling an heater with a PWM signal
 */
class Thermostat {
   private:
    float temp;
    float temp_correction;
    float temp_target;
    float prev_temp_target;
    unsigned long last_temp_reading_time;
    unsigned long temp_reading_interval;

    PID* pid;
    DHT* temp_sensor;

   private:
    /**
     * @brief Method which updates the current thermostat temperature giving
     * a specified interval
     */
    void update_temp();

   public:
    /**
     * @brief Constructor of the class Thermostat
     *
     * @param temp_reading_interval_ is the interval at wich a new temperature
     * reading is made
     * @param temp_correction_ is a correction that will be applied to the
     * temperature reading to calibrate the sensor
     */
    Thermostat(DHT* dht_sensor,
               unsigned long temp_reading_interval_ = 250,
               float temp_correction_ = 0);

    /**
     * @brief Method to return the current temperature reading
     *
     * @returns Last temperature reading
     */
    float get_temp();

    /**
     * @brief Method to update the current temperature correction
     *
     * @param new_correction is the new correction value to be applied
     */
    void set_temp_correction(float new_correction);
    float get_temp_correction();

    /**
     * @brief Method to set the current temperature target the thermostat
     * should aim for
     *
     * @param new_target is the new temperature target that should be applied
     *
     */
    void set_temp_target(float new_target);

    /**
     * @brief Updates the current proportional term of the PID controller
     *
     * @param new_p is the new proportional term to be set
     */
    void update_pid_p_term(float new_p);

    /**
     * @brief Updates the current proportional term of the PID controller
     *
     * @param new_p is the new proportional term to be set
     */
    void update_pid_i_term(float new_i);

    /**
     * @brief Updates the current proportional term of the PID controller
     *
     * @param new_p is the new proportional term to be set
     */
    void update_pid_d_term(float new_d);

    /**
     * @brief Updates the current PID term values of the PID controller
     *
     * @param new_p is the new proportional term to be set
     * @param new_i is the new integral term to be set
     * @param new_d is the new derivative term to be set
     */
    void update_pid_terms(float new_p, float new_i, float new_d);
    void update_pid_terms(pid_terms_t new_terms);
    pid_terms_t get_pid_terms();

    /**
     * @brief Main method that should run continuously.
     * It is responsible of reading the temperature and controlling the heating
     * source in order to maintain the targeted temperature
     *
     * @param temp_target is the targeted temperature that the thermostat should
     * aim for
     *
     * @return True if temperature sensor is working as expected, false otherwise
     */
    bool routine(float temp_target);
};

#endif  // !THERMOSTAT_H

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
