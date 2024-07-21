/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <eggcubator/config/configuration.h>

#ifdef UI_LOCALE_PT
#include "eggcubator/ui/language/language_pt.h"
#else

// English

#define GO_BACK_STR "Go back"
#define INCUBATE_STR "Incubation"
#define PREHEAT_STR "Preheat"
#define SETTINGS_STR "Settings"
#define SAVE_STR "Save"
#define RESET_STR "Reset"
#define MANUAL_STR "Manual"
#define CALIBRATE_STR "Calibrate"
#define EGGS_SETTINGS_STR "Eggs settings"
#define TUNE_STR "Tune"
#define STOP_INCUBATION_STR "Stop incubation"
#define TEMEPERATURE_STR "Temperature"
#define HUMIDITY_STR "Humidity"
#define TEMPERATURE_OFFSET_STR "Temp. off."
#define HUMIDITY_OFFSET_STR "Humd. off."
#define MOTOR_ROTATION_STR "Motor rot."
#define TARGET_TEMPERATURE_STR "Targt temp."
#define TARGET_HUMIDITY_STR "Targt humd."
#define PERIOD_STR "Period"
#define START_OF_ROTATION_STR "Start of rot."
#define STOP_OF_ROTATION_STR "Stop of rot."
#define ROTATION_PERIOD_STR "Rot. period"
#define HEATER_STR "Heater"
#define HUMIDIFIER_STR "Humidifier"

#define CHICKEN_STR "Chicken"
#define QUAIL_STR "Quail"
#define DUCK_STR "Duck"
#define TURKEY_STR "Turkey"
#define GOOSE_STR "Goose"
#define PIGEON_STR "Pigeon"

#endif

#endif  // !LANGUAGE_H

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
