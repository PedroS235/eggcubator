/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

#define IDDLE_MOTOR_STATE 0
#define ROTATING_MOTOR_STATE 1
#define WAITING_MOTOR_STATE 2

/**
 * @brief A motor controller class which is executed every x hours.
 */
class MotorController {
   private:
    unsigned long rotation_interval;  // In hours
    unsigned long trigger_timer;
    unsigned long rotation_timer;
    unsigned long prev_rotation;
    unsigned long start_of_rotation;
    unsigned long rotation_duration;  // In seconds
    uint8_t curr_state;

   private:
    void waiting_state();
    void rotating_state();

   public:
    /**
     * @brief Constructor of the class MotorController
     */
    MotorController();

    /**
     * @brief Method to trigger the start of motor rotation
     */
    void start_motor_rotation();

    /**
     * @brief Method to trigger the end of motor rotation
     */
    void stop_motor_rotation();

    /**
     * @brief Method to change the current rotation interval
     *
     * @param interval is the new interval that will be set (in seconds)
     */
    void set_rotation_interval_seconds(unsigned long interval);

    /**
     * @brief Method to change the current rotation interval
     *
     * @param interval is the new interval that will be set (in hours)
     */
    void set_rotation_interval_hours(unsigned long interval);

    /**
     * @brief Method to change the current rotation duration
     *
     * @param interval is the new interval that will be set (in seconds)
     */
    void set_rotation_duration_seconds(unsigned long interval);

    /**
     * @brief Method to change the current rotation duration
     *
     * @param interval is the new interval that will be set (in hours)
     */
    void set_rotation_duration_hours(unsigned long interval);

    /**
     * @brief This method is the motor controller loop function
     */
    void tick();
};

#endif  // !MOTOR_CONTROLLER_H

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
