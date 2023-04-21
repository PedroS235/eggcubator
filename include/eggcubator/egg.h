/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EGG_H
#define EGG_H
#include <Arduino.h>

#include "eggcubator/configuration.h"

/*
 * Egg types:
 * 0: Chicken
 * 1: Quail
 * 2: Duck
 * 3: Turkey
 * 4: Goose
 * 5: Pigeon
 */

/**
 * @brief Struct representing the required information about an egg
 *
 * @param type: type of the egg which it represents
 * @param incubation_days: duration of the incubation in days
 * @param eggs_rotation_period: interval between rotations (in hours)
 * @param start_of_motor_rotation: day of incubation when the eggs should start rotating
 * @param end_of_motor_rotation: day of incubation when the eggs should stop rotating
 * @param target_temp: the desired targeted temperature
 * @param target_humd: the desired targeted humidity
 */
typedef struct {
    uint8_t type;
    uint8_t incubation_days;
    uint8_t eggs_rotation_period;
    uint8_t start_of_motor_rotation;
    uint8_t end_of_motor_rotation;
    float target_temp;
    float target_humd;
} egg_t;

inline egg_t chicken_egg = {EGG_CHICKEN_TYPE,
                            EGG_CHICKEN_INCUBATION_PERIOD,
                            EGG_CHICKEN_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_TARGET_TEMP,
                            EGG_CHICKEN_TARGET_HUMD};

inline egg_t quail_egg = {EGG_QUAIL_TYPE,
                          EGG_QUAIL_INCUBATION_PERIOD,
                          EGG_QUAIL_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_START_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_TARGET_TEMP,
                          EGG_QUAIL_TARGET_HUMD};

inline egg_t duck_egg = {EGG_DUCK_TYPE,
                         EGG_DUCK_INCUBATION_PERIOD,
                         EGG_DUCK_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_START_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_TARGET_TEMP,
                         EGG_DUCK_TARGET_HUMD};

inline egg_t turkey_egg = {EGG_TURKEY_TYPE,
                           EGG_TURKEY_INCUBATION_PERIOD,
                           EGG_TURKEY_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_START_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_TARGET_TEMP,
                           EGG_TURKEY_TARGET_HUMD};

inline egg_t goose_egg = {EGG_GOOSE_TYPE,
                          EGG_GOOSE_INCUBATION_PERIOD,
                          EGG_GOOSE_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_START_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_TARGET_TEMP,
                          EGG_GOOSE_TARGET_HUMD};

inline egg_t pigeon_egg = {EGG_PIGEON_TYPE,
                           EGG_PIGEON_INCUBATION_PERIOD,
                           EGG_PIGEON_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_START_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_TARGET_TEMP,
                           EGG_PIGEON_TARGET_HUMD};

#endif  // !EGG_H

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
