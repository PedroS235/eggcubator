/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef MOVING_AVG_FILTER_H
#define MOVING_AVG_FILTER_H

#define MOVING_AVG_FILTER_WINDOW_SIZE 10

#include <Arduino.h>

/**
 * @brief: Simple filter in order to smooth out sensor readings and reduce
 * the impact of sensor noises
 */
class MovingAvgFilter {
   private:
    float readings[MOVING_AVG_FILTER_WINDOW_SIZE];
    uint8_t curr_index = 0;

   public:
    /**
     * @brief Constructor of the class MovingAvgFilter
     */
    MovingAvgFilter() {
        for (int i = 0; i < MOVING_AVG_FILTER_WINDOW_SIZE; i++) {
            readings[i] = 0;
        }
    }

    /**
     * @brief Computes the filtered value from the current measured value
     *
     * @param current_value is the current measured value of the sensor
     *
     * @return Filtered value
     */
    float compute(float current_value) {
        readings[curr_index] = current_value;
        curr_index = (curr_index + 1) % MOVING_AVG_FILTER_WINDOW_SIZE;

        float sum = 0;
        for (int i = 0; i < MOVING_AVG_FILTER_WINDOW_SIZE; i++) {
            sum += readings[i];
        }

        return sum / MOVING_AVG_FILTER_WINDOW_SIZE;
    }
};

#endif  // !MOVING_AVG_FILTER_H

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
