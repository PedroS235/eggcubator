/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include "eggcubator/core/timer.h"

using namespace eggcubator;
Timer::Timer() {
    _time_interval = 1000;
    _elapsed_time = millis();
    _time = {0, 0, 0, 0};
    _drift = 0;
}

uint8_t Timer::get_day() { return _time.day; }

uint8_t Timer::get_hour() { return _time.hour; }

uint8_t Timer::get_minute() { return _time.minute; }

uint8_t Timer::get_seconds() { return _time.second; }

eggcubator::time_t Timer::get_time_t() { return _time; }

void Timer::print_time() {
    if (_time.day > 0) {
        Serial.print(_time.day);
        Serial.println(" days");
    } else {
        Serial.print(_time.hour);
        Serial.print(":");
        Serial.print(_time.minute);
        Serial.print(":");
        Serial.println(_time.second);
    }
}

void Timer::start() {
    _elapsed_time = millis();
    _is_running = true;
    _time = {0, 0, 0, 0};
}

void Timer::update() {
    if (_is_running) {
        unsigned long now = millis();
        if (now - _elapsed_time + _drift >= _time_interval) {
            _drift = now - _elapsed_time + _drift - _time_interval;
            _elapsed_time = now;
            _time.second++;
        }

        if (_time.second == 60) {
            _time.minute++;
            _time.second = 0;
        }

        if (_time.minute == 60) {
            _time.hour++;
            _time.minute = 0;
        }

        if (_time.hour == 24) {
            _time.day++;
            _time.hour = 0;
        }
    }
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
