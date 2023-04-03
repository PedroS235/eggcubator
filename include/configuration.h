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

#endif // !CONFIGURATION_H

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
