/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

namespace eggcubator {
typedef struct {
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_t;

class Timer {
   private:
    time_t time;
    unsigned long elapsed_time;
    unsigned long drift;
    unsigned long time_interval;
    bool is_running = false;

   public:
    Timer();
    uint8_t get_day();
    uint8_t get_hour();
    uint8_t get_minute();
    uint8_t get_seconds();
    time_t get_time_t();
    void print_time();
    void update();
    void start();
};
};  // namespace eggcubator

#endif  // !TIMER_H

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
