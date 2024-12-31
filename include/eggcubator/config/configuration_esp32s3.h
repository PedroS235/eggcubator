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

#ifndef CONFIGURATION_ESP32S3_H
#define CONFIGURATION_ESP32S3_H

// Extras
#define WATER_LEVEL_SENSOR_PIN 1
#define FAN_PIN 10

// -----------------------------------------------------------------------------
// |                           Heater Config Section                           |
// -----------------------------------------------------------------------------

#define HEATER_PIN 7
#define HEATER_SENSOR_PIN 6  // Thermistor
#define HEATER_MIN_TEMP -10.0
#define HEATER_MAX_TEMP 40.0
#define HEATER_PID_KP 10.0
#define HEATER_PID_KI 1.0
#define HEATER_PID_KD 1.5
#define HEATER_CONTROL_TYPE 0  // 0: PID, 1: BANGBANG

// -----------------------------------------------------------------------------
// |                         Humidifier Config Section                         |
// -----------------------------------------------------------------------------

#define HUMIDIFIER_PIN
#define HUMIDIFIER_SENSOR_PIN 2
#define HUMIDIFIER_SENSOR_TYPE DHT11
#define HUMIDIFIER_SERVO_PIN 11
#define HUMIDIFIER_PID_KP 5.0
#define HUMIDIFIER_PID_KI 0.0
#define HUMIDIFIER_PID_KD 0.0

// -----------------------------------------------------------------------------
// |                            Motor Config Section                           |
// -----------------------------------------------------------------------------

#define MOTOR_PIN 9  // Deprecated in favor of stepper motor
#define MOTOR_IN1 8
#define MOTOR_IN2 9
#define MOTOR_IN3 10
#define MOTOR_IN4 11
#define MOTOR_ROTATION_DURATION 5  // in seconds

// -----------------------------------------------------------------------------
// |                             UI Config Section                             |
// -----------------------------------------------------------------------------

/* To know what is your oled type, you can check it in U8g2 repo,
 * found here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
 */

#define UI_LOCALE_EN                 // use _PT for portuguese
#define UI_BOOTSCREEN_DURATION 1000  // in milliseconds
#define UI_REFRESH_RATE 1 / 30       // 1/Hz
#define UI_OLED_TYPE \
    U8G2_SH1106_128X64_NONAME_F_HW_I2C  // Make sure to use full frame buffer
#define UI_I2C_SCK_PIN 12               // 22 for esp32 dev
#define UI_I2C_SDA_PIN 13               // 21 for esp32 dev
#define UI_SPEAKER_PIN 6
#define UI_ENCODER_CLK_PIN 3
#define UI_ENCODER_DT_PIN 4
#define UI_ENCODER_SW_PIN 5

// -----------------------------------------------------------------------------
// |                              Egg Config Section                           |
// -----------------------------------------------------------------------------

// Chicken eggs
#define EGG_CHICKEN_TYPE 0  // DO NOT CHANGE THIS VALUE
#define EGG_CHICKEN_INCUBATION_PERIOD 21
#define EGG_CHICKEN_MOTOR_ROTATION_PERIOD 1
#define EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD 2
#define EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD 3
#define EGG_CHICKEN_TARGET_TEMP 37.7
#define EGG_CHICKEN_TARGET_HUMD 55.0

// Quail eggs
#define EGG_QUAIL_TYPE 1  // DO NOT CHANGE THIS VALUE1
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

#endif  // !CONFIGURATION_ESP32S3_H

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
