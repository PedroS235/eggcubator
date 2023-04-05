/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef INCUBATION_ROUTINE_H
#define INCUBATION_ROUTINE_H
#include <eggcubator/configuration.h>
#include <eggcubator/egg.h>
#include <eggcubator/module/motor_controller.h>
#include <eggcubator/timer.h>

using namespace eggcubator;

// States
#define IDDLE_INCUBATION_STATE 0
#define BEFORE_INCUBATION_STATE 1
#define IN_INCUBATION_STATE 2
#define AFTER_INCUBATION_STATE 3

class IncubationRoutine {
   private:
    uint8_t curr_state;
    eggcubator::time_t time_left;
    Timer curr_time;
    unsigned long total_time;
    egg_t *curr_egg;
    MotorController motor_controller;

   private:
    void before_incubation_state();
    void in_incubation_state();
    void after_incubation_state();

   public:
    IncubationRoutine();
    eggcubator::time_t get_time_left();
    unsigned long get_total_time();
    Timer get_curr_time();
    void start_incubation(egg_t *egg);

    bool routine();
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
