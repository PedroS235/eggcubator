/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "eggcubator/module/eeprom_manager.h"

#include "EEPROM.h"
#include "eggcubator/configuration.h"
#include "eggcubator/egg.h"

// TODO: Add to eeprom the temperature offset and humidity offset correction

void eeprom_setup() {
    EEPROM.begin(EEPROM_SIZE);
    // Check if the eeprom varies from the default values
}

void eeprom_write_egg_config(const egg_t *egg_config, int address) {
    int pointer = address;
    EEPROM.writeByte(pointer, egg_config->type);
    pointer += sizeof(uint8_t);
    EEPROM.writeByte(pointer, egg_config->incubation_days);
    pointer += sizeof(uint8_t);
    EEPROM.writeByte(pointer, egg_config->eggs_rotation_period);
    pointer += sizeof(uint8_t);
    EEPROM.writeByte(pointer, egg_config->start_of_motor_rotation);
    pointer += sizeof(uint8_t);
    EEPROM.writeByte(pointer, egg_config->end_of_motor_rotation);
    pointer += sizeof(uint8_t);
    EEPROM.writeFloat(pointer, egg_config->target_temp);
    pointer += sizeof(float);
    EEPROM.writeFloat(pointer, egg_config->target_humd);
    EEPROM.commit();
}

void eeprom_read_egg_config(egg_t *egg_config, int address) {
    int pointer = address;
    egg_config->type = EEPROM.readByte(pointer);
    pointer += sizeof(uint8_t);
    egg_config->incubation_days = EEPROM.readByte(pointer);
    pointer += sizeof(uint8_t);
    egg_config->eggs_rotation_period = EEPROM.readByte(pointer);
    pointer += sizeof(uint8_t);
    egg_config->start_of_motor_rotation = EEPROM.readByte(pointer);
    pointer += sizeof(uint8_t);
    egg_config->end_of_motor_rotation = EEPROM.readByte(pointer);
    pointer += sizeof(uint8_t);
    egg_config->target_temp = EEPROM.readFloat(pointer);
    pointer += sizeof(float);
    egg_config->target_humd = EEPROM.readFloat(pointer);
}

void eeprom_write_pid(const pid_terms_t pid_terms, int address) {
    int pointer = address;
    EEPROM.writeFloat(pointer, pid_terms.kp);
    pointer += sizeof(float);
    EEPROM.writeFloat(pointer, pid_terms.ki);
    pointer += sizeof(float);
    EEPROM.writeFloat(pointer, pid_terms.kd);
    EEPROM.commit();
}

void eeprom_read_pid(pid_terms_t *pid_terms, int address) {
    int pointer = address;
    pid_terms->kp = EEPROM.readFloat(pointer);
    pointer += sizeof(float);
    pid_terms->ki = EEPROM.readFloat(pointer);
    pointer += sizeof(float);
    pid_terms->kd = EEPROM.readFloat(pointer);
}

void eeprom_write_temp_pid(const pid_terms_t pid_terms) {
    eeprom_write_pid(pid_terms, EEPROM_TEMP_PID_ADDRESS);
}
void eeprom_read_temp_pid(pid_terms_t *pid_terms) {
    eeprom_read_pid(pid_terms, EEPROM_TEMP_PID_ADDRESS);
}

void eeprom_write_servo_pid(const pid_terms_t pid_terms) {
    eeprom_write_pid(pid_terms, EEPROM_SERVO_PID_ADDRESS);
}
void eeprom_read_servo_pid(pid_terms_t *pid_terms) {
    eeprom_read_pid(pid_terms, EEPROM_SERVO_PID_ADDRESS);
}

void eeprom_write_egg_rotation_duration(const uint8_t duration) {
    EEPROM.writeULong(EEPROM_EGG_ROTATION_DURATION_ADDRESS, duration);
}
uint8_t eeprom_read_egg_rotation_duration() {
    return EEPROM.readULong(EEPROM_EGG_ROTATION_DURATION_ADDRESS);
}

void eeprom_write_chicken_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_CHICKEN_EGG_CONFIG_ADDRESS);
}
void eeprom_read_chicken_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_CHICKEN_EGG_CONFIG_ADDRESS);
}

void eeprom_write_quail_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_QUAIL_EGG_CONFIG_ADDRESS);
}
void eeprom_read_quail_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_QUAIL_EGG_CONFIG_ADDRESS);
}

void eeprom_write_duck_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_DUCK_EGG_CONFIG_ADDRESS);
}
void eeprom_read_duck_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_DUCK_EGG_CONFIG_ADDRESS);
}

void eeprom_write_goose_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_GOOSE_EGG_CONFIG_ADDRESS);
}
void eeprom_read_goose_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_GOOSE_EGG_CONFIG_ADDRESS);
}

void eeprom_write_turkey_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_TURKEY_EGG_CONFIG_ADDRESS);
}
void eeprom_read_turkey_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_TURKEY_EGG_CONFIG_ADDRESS);
}

void eeprom_write_pigeon_egg_config(const egg_t *egg_config) {
    eeprom_write_egg_config(egg_config, EEPROM_PIGEON_EGG_CONFIG_ADDRESS);
}
void eeprom_read_pigeon_egg_config(egg_t *egg_config) {
    eeprom_read_egg_config(egg_config, EEPROM_PIGEON_EGG_CONFIG_ADDRESS);
}

void eeprom_reset() {
    egg_t chicken_egg = {EGG_CHICKEN_TYPE,
                         EGG_CHICKEN_INCUBATION_PERIOD,
                         EGG_CHICKEN_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_TARGET_TEMP,
                         EGG_CHICKEN_TARGET_HUMD};

    egg_t quail_egg = {EGG_QUAIL_TYPE,
                       EGG_QUAIL_INCUBATION_PERIOD,
                       EGG_QUAIL_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_START_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_TARGET_TEMP,
                       EGG_QUAIL_TARGET_HUMD};

    egg_t duck_egg = {EGG_DUCK_TYPE,
                      EGG_DUCK_INCUBATION_PERIOD,
                      EGG_DUCK_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_START_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_TARGET_TEMP,
                      EGG_DUCK_TARGET_HUMD};

    egg_t turkey_egg = {EGG_TURKEY_TYPE,
                        EGG_TURKEY_INCUBATION_PERIOD,
                        EGG_TURKEY_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_START_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_TARGET_TEMP,
                        EGG_TURKEY_TARGET_HUMD};

    egg_t goose_egg = {EGG_GOOSE_TYPE,
                       EGG_GOOSE_INCUBATION_PERIOD,
                       EGG_GOOSE_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_START_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_TARGET_TEMP,
                       EGG_GOOSE_TARGET_HUMD};

    egg_t pigeon_egg = {EGG_PIGEON_TYPE,
                        EGG_PIGEON_INCUBATION_PERIOD,
                        EGG_PIGEON_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_START_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_TARGET_TEMP,
                        EGG_PIGEON_TARGET_HUMD};

    eeprom_write_chicken_egg_config(&chicken_egg);
    eeprom_write_quail_egg_config(&quail_egg);
    eeprom_write_duck_egg_config(&duck_egg);
    eeprom_write_turkey_egg_config(&turkey_egg);
    eeprom_write_goose_egg_config(&goose_egg);
    eeprom_write_pigeon_egg_config(&pigeon_egg);

    eeprom_write_temp_pid({PID_TEMP_KP, PID_TEMP_KI, PID_TEMP_KD});
    eeprom_write_servo_pid({PID_SERVO_KP, PID_SERVO_KI, PID_SERVO_KD});

    eeprom_write_egg_rotation_duration(EGG_MOTOR_ROTATION_DURATION);
}

bool is_eeprom_mismatched() {
    bool mismatched = false;

    egg_t chicken_egg = {EGG_CHICKEN_TYPE,
                         EGG_CHICKEN_INCUBATION_PERIOD,
                         EGG_CHICKEN_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD,
                         EGG_CHICKEN_TARGET_TEMP,
                         EGG_CHICKEN_TARGET_HUMD};

    egg_t quail_egg = {EGG_QUAIL_TYPE,
                       EGG_QUAIL_INCUBATION_PERIOD,
                       EGG_QUAIL_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_START_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD,
                       EGG_QUAIL_TARGET_TEMP,
                       EGG_QUAIL_TARGET_HUMD};

    egg_t duck_egg = {EGG_DUCK_TYPE,
                      EGG_DUCK_INCUBATION_PERIOD,
                      EGG_DUCK_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_START_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD,
                      EGG_DUCK_TARGET_TEMP,
                      EGG_DUCK_TARGET_HUMD};

    egg_t goose_egg = {EGG_GOOSE_TYPE,
                       EGG_GOOSE_INCUBATION_PERIOD,
                       EGG_GOOSE_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_START_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD,
                       EGG_GOOSE_TARGET_TEMP,
                       EGG_GOOSE_TARGET_HUMD};

    egg_t turkey_egg = {EGG_TURKEY_TYPE,
                        EGG_TURKEY_INCUBATION_PERIOD,
                        EGG_TURKEY_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_START_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD,
                        EGG_TURKEY_TARGET_TEMP,
                        EGG_TURKEY_TARGET_HUMD};

    egg_t pigeon_egg = {EGG_PIGEON_TYPE,
                        EGG_PIGEON_INCUBATION_PERIOD,
                        EGG_PIGEON_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_START_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD,
                        EGG_PIGEON_TARGET_TEMP,
                        EGG_PIGEON_TARGET_HUMD};

    egg_t chicken_egg_read;
    egg_t quail_egg_read;
    egg_t duck_egg_read;
    egg_t goose_egg_read;
    egg_t turkey_egg_read;
    egg_t pigeon_egg_read;

    eeprom_read_egg_config(&chicken_egg_read, EEPROM_CHICKEN_EGG_CONFIG_ADDRESS);
    eeprom_read_egg_config(&quail_egg_read, EEPROM_QUAIL_EGG_CONFIG_ADDRESS);
    eeprom_read_egg_config(&duck_egg_read, EEPROM_DUCK_EGG_CONFIG_ADDRESS);
    eeprom_read_egg_config(&turkey_egg_read, EEPROM_TURKEY_EGG_CONFIG_ADDRESS);
    eeprom_read_egg_config(&goose_egg_read, EEPROM_GOOSE_EGG_CONFIG_ADDRESS);
    eeprom_read_egg_config(&turkey_egg_read, EEPROM_TURKEY_EGG_CONFIG_ADDRESS);

    if (chicken_egg_read.type != chicken_egg.type ||
        chicken_egg_read.incubation_days != chicken_egg.incubation_days ||
        chicken_egg_read.eggs_rotation_period != chicken_egg.eggs_rotation_period ||
        chicken_egg_read.start_of_motor_rotation !=
            chicken_egg.start_of_motor_rotation ||
        chicken_egg_read.end_of_motor_rotation != chicken_egg.end_of_motor_rotation ||
        chicken_egg_read.target_temp != chicken_egg.target_temp ||
        chicken_egg_read.target_humd != chicken_egg.target_humd) {
        return true;
    }

    if (quail_egg_read.type != quail_egg.type ||
        quail_egg_read.incubation_days != quail_egg.incubation_days ||
        quail_egg_read.eggs_rotation_period != quail_egg.eggs_rotation_period ||
        quail_egg_read.start_of_motor_rotation != quail_egg.start_of_motor_rotation ||
        quail_egg_read.end_of_motor_rotation != quail_egg.end_of_motor_rotation ||
        quail_egg_read.target_temp != quail_egg.target_temp ||
        quail_egg_read.target_humd != quail_egg.target_humd) {
        return true;
    }

    if (duck_egg_read.type != duck_egg.type ||
        duck_egg_read.incubation_days != duck_egg.incubation_days ||
        duck_egg_read.eggs_rotation_period != duck_egg.eggs_rotation_period ||
        duck_egg_read.start_of_motor_rotation != duck_egg.start_of_motor_rotation ||
        duck_egg_read.end_of_motor_rotation != duck_egg.end_of_motor_rotation ||
        duck_egg_read.target_temp != duck_egg.target_temp ||
        duck_egg_read.target_humd != duck_egg.target_humd) {
        return true;
    }

    if (goose_egg_read.type != goose_egg.type ||
        goose_egg_read.incubation_days != goose_egg.incubation_days ||
        goose_egg_read.eggs_rotation_period != goose_egg.eggs_rotation_period ||
        goose_egg_read.start_of_motor_rotation != goose_egg.start_of_motor_rotation ||
        goose_egg_read.end_of_motor_rotation != goose_egg.end_of_motor_rotation ||
        goose_egg_read.target_temp != goose_egg.target_temp ||
        goose_egg_read.target_humd != goose_egg.target_humd) {
        return true;
    }

    if (turkey_egg_read.type != turkey_egg.type ||
        turkey_egg_read.incubation_days != turkey_egg.incubation_days ||
        turkey_egg_read.eggs_rotation_period != turkey_egg.eggs_rotation_period ||
        turkey_egg_read.start_of_motor_rotation != turkey_egg.start_of_motor_rotation ||
        turkey_egg_read.end_of_motor_rotation != turkey_egg.end_of_motor_rotation ||
        turkey_egg_read.target_temp != turkey_egg.target_temp ||
        turkey_egg_read.target_humd != turkey_egg.target_humd) {
        return true;
    }

    if (pigeon_egg_read.type != pigeon_egg.type ||
        pigeon_egg_read.incubation_days != pigeon_egg.incubation_days ||
        pigeon_egg_read.eggs_rotation_period != pigeon_egg.eggs_rotation_period ||
        pigeon_egg_read.start_of_motor_rotation != pigeon_egg.start_of_motor_rotation ||
        pigeon_egg_read.end_of_motor_rotation != pigeon_egg.end_of_motor_rotation ||
        pigeon_egg_read.target_temp != pigeon_egg.target_temp ||
        pigeon_egg_read.target_humd != pigeon_egg.target_humd) {
        return true;
    }

    // TODO: missing pid

    if (eeprom_read_egg_rotation_duration() != EGG_MOTOR_ROTATION_DURATION) {
        return true;
    }

    return false;
}

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
