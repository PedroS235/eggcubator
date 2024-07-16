/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef INCUBATION_ROUTINE_H
#define INCUBATION_ROUTINE_H
#include <eggcubator/config/configuration.h>
#include <eggcubator/core/motor_controller.h>
#include <eggcubator/core/timer.h>
#include <eggcubator/egg.h>

using namespace eggcubator;

// Incubation States
#define IDDLE_INCUBATION_STATE 0
#define BEFORE_INCUBATION_STATE 1
#define IN_INCUBATION_STATE 2
#define AFTER_INCUBATION_STATE 3

/**
 * @brief Class reponsible for the routine of the incubation.
 * It's aim is to be in charge in checking when to start and end an incubation cycle
 * which depends on the type of egg. In addition, it is also reposible in triggering
 * when the motor should start rotating the eggs as well as ending the rotation.
 */
class IncubationRoutine {
   private:
    uint8_t curr_state;
    Timer curr_time;
    egg_t *curr_egg;
    MotorController motor_controller;

   private:
    /**
     * @brief Method which represetns the BEFORE_INCUBATION_STATE
     */
    void before_incubation_state();

    /**
     * @brief Method which represetns the IN_INCUBATION_STATE
     */
    void in_incubation_state();

    /**
     * @brief Method which represetns the AFTER_INCUBATION_STATE
     */
    void after_incubation_state();

   public:
    /**
     * @brief Constructor of the class IncubationRoutine
     */
    IncubationRoutine();
    /**
     * @brief Method which returns the current time elapsed of incubation
     *
     * @returns current time elapsed in form of a time_t struct
     */
    Timer get_curr_time();

    /**
     * @brief Method which triggers the incubation to start taking place
     *
     * @param egg: egg for wihch the incubation should aim for
     */
    void start_incubation(egg_t *egg);
    void stop_incubation();

    /**
     * @brief Method which acts like the internal loop cycle for the incubation routine
     *
     * @returns true if incubation is in place, false otherwise
     */
    void task(void *pvParameters);

    egg_t curr_egg_in_incubation();

    bool in_incubation();
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
