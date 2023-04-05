/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 *
 * ----------------------------------------------------------------------------
 *
 * This is the configuration file for the EggCubator controller.
 * Here you can modify some of the default values utilized for the controller.
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// ------------------------
// - Sensor Types Section -
// ------------------------

// DHT temperate & humidity sensor type
// Possible values are DHT11 or DHT22
#define TYPE_DHT DHT11

// Oled display type
// To know what is your desplay type, you can check it in U8g2 repo,
// found here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
#define TYPE_DISPLAY U8G2_SH1106_128X64_NONAME_1_HW_I2C

// ---------------
// - PID Section -
// ---------------

// Temperature PID values
#define PID_TEMP_KP 1
#define PID_TEMP_KI 0.2
#define PID_TEMP_KD 0.2

// Servo PID values
#define PID_SERVO_KP 1
#define PID_SERVO_KI 0.2
#define PID_SERVO_KD 0.2

// -----------------------------
// - Egg Configuration Section -
// -----------------------------

// Chicken eggs
#define EGG_CHICKEN_TYPE 0  // DO NOT CHANGE THIS VALUE
#define EGG_CHICKEN_INCUBATION_PERIOD 21
#define EGG_CHICKEN_MOTOR_ROTATION_PERIOD 1
#define EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD 2
#define EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_CHICKEN_TARGET_TEMP 37.7
#define EGG_CHICKEN_TARGET_HUMD 55.0

// Quail eggs
#define EGG_QUAIL_TYPE  // DO NOT CHANGE THIS VALUE1
#define EGG_QUAIL_INCUBATION_PERIOD 18
#define EGG_QUAIL_MOTOR_ROTATION_PERIOD 1
#define EGG_QUAIL_START_MOTOR_ROTATION_PERIOD 2
#define EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_QUAIL_TARGET_TEMP 37.3
#define EGG_QUAIL_TARGET_HUMD 40.0

// Duck eggs
#define EGG_DUCK_TYPE 2  // DO NOT CHANGE THIS VALUE
#define EGG_DUCK_INCUBATION_PERIOD 28
#define EGG_DUCK_MOTOR_ROTATION_PERIOD 1
#define EGG_DUCK_START_MOTOR_ROTATION_PERIOD 2
#define EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_DUCK_TARGET_TEMP 37.5
#define EGG_DUCK_TARGET_HUMD 55.0

// Turkey eggs
#define EGG_TURKEY_TYPE 3  // DO NOT CHANGE THIS VALUE
#define EGG_TURKEY_INCUBATION_PERIOD 28
#define EGG_TURKEY_MOTOR_ROTATION_PERIOD 1
#define EGG_TURKEY_START_MOTOR_ROTATION_PERIOD 2
#define EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_TURKEY_TARGET_TEMP 37.7
#define EGG_TURKEY_TARGET_HUMD 55.0

// Goose eggs
#define EGG_GOOSE_TYPE 4  // DO NOT CHANGE THIS VALUE
#define EGG_GOOSE_INCUBATION_PERIOD 28
#define EGG_GOOSE_MOTOR_ROTATION_PERIOD 1
#define EGG_GOOSE_START_MOTOR_ROTATION_PERIOD 2
#define EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_GOOSE_TARGET_TEMP 37.7
#define EGG_GOOSE_TARGET_HUMD 80.0

// Pigeon eggs
#define EGG_PIGEON_TYPE 5  // DO NOT CHANGE THIS VALUE
#define EGG_PIGEON_INCUBATION_PERIOD 28
#define EGG_PIGEON_MOTOR_ROTATION_PERIOD 1
#define EGG_PIGEON_START_MOTOR_ROTATION_PERIOD 2
#define EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_PIGEON_TARGET_TEMP 37.5
#define EGG_PIGEON_TARGET_HUMD 57.0

#define EGG_MOTOR_ROTATION_DURATION 5  // seconds

#endif                                 // !CONFIGURATION_H

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
