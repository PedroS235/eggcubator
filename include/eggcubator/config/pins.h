/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 *
 * ----------------------------------------------------------------------------
 *
 * This file contains the GPIO pins which are associated with each sensor
 * or component connected to the board.
 * You may change any of the defined pins to your specific pins.
 */

#ifndef PINS_H
#define PINS_H

#define PIN_WATER_LEVEL_SENSOR 1
#define PIN_DHT 2

#define PIN_ENCODER_CLK 3
#define PIN_ENCODER_DT 4
#define PIN_ENCODER_SW 5

#define PIN_BUZZER 6
#define PIN_THERMISTOR 7
#define PIN_HEATER 8
#define PIN_MOTOR 9
#define PIN_FAN 10
#define PIN_SERVO 11

#define PIN_I2C_SCK 12  // 22 for esp32 dev
#define PIN_I2C_SDA 13  // 21 for esp32 dev

#endif  // !PINS_H

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
