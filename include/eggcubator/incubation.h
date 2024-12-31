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
#include <eggcubator/egg_factory.h>

#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"

using namespace eggcubator;

// Incubation States
typedef enum {
    IDDLE_INCUBATION_STATE,
    BEFORE_INCUBATION_STATE,
    IN_INCUBATION_STATE,
    AFTER_INCUBATION_STATE,
} incubation_state_e;

const char *state_to_string(incubation_state_e state);

/**
 * @brief Class reponsible for the routine of the incubation.
 * It's aim is to be in charge in checking when to start and end an incubation cycle
 * which depends on the type of egg. In addition, it is also reposible in triggering
 * when the motor should start rotating the eggs as well as ending the rotation.
 */
class IncubationRoutine {
   private:
    incubation_state_e curr_state;
    Timer curr_time;
    egg_t curr_egg;
    Heater *_heater;
    Humidifier *_humidifier;
    MotorController motor_controller;
    bool started_motor_rotation = false;
    bool stoped_motor_rotation = false;

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
    IncubationRoutine(Heater *heater, Humidifier *humidifier);
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
    void start_incubation(egg_t egg);
    void stop_incubation();
    void rotate_motor();

    /**
     * @brief Method which acts like the internal loop cycle for the incubation routine
     *
     * @returns true if incubation is in place, false otherwise
     */
    void task(void *pvParameters);

    egg_t curr_egg_in_incubation();

    bool in_incubation();

    void log_stats();

    void set_temperature(float temp);
    void set_humidity(float humd);

    void set_motor_rotation(unsigned long duration);
    unsigned long get_motor_rotation();
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
