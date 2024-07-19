/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EEPROM_MANANGER
#define EEPROM_MANANGER

#include <EEPROM.h>

#include "eggcubator/egg_factory.h"
#include "eggcubator/extras/pid_control.h"

#define EEPROM_SIZE 512
#define EEPROM_START 50

#define EEPROM_CHICKEN_EGG_CONFIG_ADDRESS EEPROM_START
#define EEPROM_QUAIL_EGG_CONFIG_ADDRESS EEPROM_START + sizeof(egg_t)
#define EEPROM_DUCK_EGG_CONFIG_ADDRESS EEPROM_START + 2 * sizeof(egg_t)
#define EEPROM_TURKEY_EGG_CONFIG_ADDRESS EEPROM_START + 3 * sizeof(egg_t)
#define EEPROM_GOOSE_EGG_CONFIG_ADDRESS EEPROM_START + 4 * sizeof(egg_t)
#define EEPROM_PIGEON_EGG_CONFIG_ADDRESS EEPROM_START + 5 * sizeof(egg_t)

#define EEPROM_TEMP_PID_ADDRESS EEPROM_START + 6 * sizeof(egg_t)
#define EEPROM_SERVO_PID_ADDRESS EEPROM_TEMP_PID_ADDRESS + 3 * sizeof(float)

#define EEPROM_EGG_ROTATION_DURATION_ADDRESS \
    EEPROM_SERVO_PID_ADDRESS + 3 * sizeof(float)

void eeprom_setup();

void eeprom_write_egg_config(const egg_t *egg_config, int address);
void eeprom_read_egg_config(egg_t *egg_config, int address);

void eeprom_write_pid(const pid_config_t pid_terms, int address);
void eeprom_read_pid(pid_config_t *pid_terms, int address);

void eeprom_write_temp_pid(const pid_config_t pid_terms);
void eeprom_read_temp_pid(pid_config_t *pid_terms);

void eeprom_write_servo_pid(const pid_config_t pid_terms);
void eeprom_read_servo_pid(pid_config_t *pid_terms);

void eeprom_write_egg_rotation_duration(const uint8_t duration);
uint8_t eeprom_read_egg_rotation_duration();

void eeprom_write_chicken_egg_config(const egg_t *egg_config);
void eeprom_read_chicken_egg_config(egg_t *egg_config);

void eeprom_write_quail_egg_config(const egg_t *egg_config);
void eeprom_read_quail_egg_config(egg_t *egg_config);

void eeprom_write_duck_egg_config(const egg_t *egg_config);
void eeprom_read_duck_egg_config(egg_t *egg_config);

void eeprom_write_turkey_egg_config(const egg_t *egg_config);
void eeprom_read_turkey_egg_config(egg_t *egg_config);

void eeprom_write_goose_egg_config(const egg_t *egg_config);
void eeprom_read_goose_egg_config(egg_t *egg_config);

void eeprom_write_pigeon_egg_config(const egg_t *egg_config);
void eeprom_read_pigeon_egg_config(egg_t *egg_config);

bool is_eeprom_mismatched();

void eeprom_reset();

#endif  // !EEPROM_MANANGER

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
