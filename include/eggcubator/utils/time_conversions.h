/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef TIME_CONVERSIONS_H
#define TIME_CONVERSIONS_H

#define DAY_TO_SEC 86400
#define HOUR_IN_MILLIS 3600000
#define HOUR_IN_SEC 3600
#define SEC_IN_MILLIS 1000

inline unsigned long sec_to_millis(unsigned long secs) { return secs * SEC_IN_MILLIS; }
inline unsigned long hour_to_millis(unsigned long hours) {
    return hours * HOUR_IN_MILLIS;
}
inline unsigned long day_to_millis(unsigned long days) {
    return days * DAY_TO_SEC * SEC_IN_MILLIS;
}

#endif  // !TIME_CONVERSIONS_H

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
