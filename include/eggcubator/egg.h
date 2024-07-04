/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EGG_H
#define EGG_H
#include <Arduino.h>

#include "eggcubator/config/configuration.h"

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

egg_t *get_chicken_egg_config();
void update_chicken_egg_config(egg_t egg);

egg_t *get_quail_egg_config();
void updat_quail_egg_config(egg_t egg);

egg_t *get_duck_egg_config();
void update_duck_egg_config(egg_t egg);

egg_t *get_turkey_egg_config();
void update_turkey_egg_config(egg_t egg);

egg_t *get_goose_egg_config();
void update_goose_egg_config(egg_t egg);

egg_t *get_pigeon_egg_config();
void update_pigeon_egg_config(egg_t egg);

void print_egg_config(egg_t config);

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
