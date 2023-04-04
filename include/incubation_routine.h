/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef INCUBATION_ROUTINE_H
#define INCUBATION_ROUTINE_H
#include <cstdint>

// States
#define IDDLE_INCUBATION_STATE 0
#define BEFORE_INCUBATION_STATE 1
#define IN_INCUBATION_STATE 2
#define AFTER_INCUBATION_STATE 3

class IncubationRoutine {
   private:
    uint8_t curr_state = 0;
    unsigned int time_left;
    unsigned long curr_time;
    unsigned long total_time;

   private:
    void iddle_incubation_state();
    void before_incubation_state();
    void in_incubation_state();
    void after_incubation_state();

   public:
    IncubationRoutine();
    unsigned long get_time_left();
    unsigned long get_total_time();
    unsigned long get_curr_time();

    void routine();
};

#endif  // !INCUBATION_ROUTINE_H

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
