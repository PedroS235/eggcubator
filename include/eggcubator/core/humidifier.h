/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include <DHT.h>

#include "eggcubator/extras/pid_control.h"

// TODO: also read temperature if needed. could be used to compare with thermistor
// reading

class Humidifier {
   private:
    float humidity;
    float humidity_correction;
    float humidity_target;
    float prev_humidity_target;
    unsigned long last_humidity_reading_time;
    unsigned long humidity_reading_interval;

    PID* pid;
    DHT* sensor;

   private:
    void update_humidity();

   public:
    Humidifier(unsigned long humidity_reading_interval_ = 2000,
               float humidity_correction_ = 0);

    /**
     * @brief Method to return the current humidity reading
     *
     * @returns Last humidity reading
     */
    float get_humidity();

    /**
     * @brief Method to update the current humidity correction
     *
     * @param new_correction is the new correction value to be applied
     */
    void set_humidity_correction(float new_correction);
    float get_humidity_correction();

    /**
     * @brief Method to set the current humidity target the thermostat
     * should aim for
     *
     * @param new_target is the new humidity target that should be applied
     *
     */
    void set_humidity_target(float new_target);

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
    bool routine(float humidity_target_);
};

#endif  // !HUMIDIFIER_H

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
