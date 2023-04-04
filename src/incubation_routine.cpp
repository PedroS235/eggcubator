/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <incubation_routine.h>

void IncubationRoutine::routine() {
    switch (curr_state) {
        case IDDLE_INCUBATION_STATE:
            iddle_incubation_state();
            break;
        case BEFORE_INCUBATION_STATE:
            before_incubation_state();
            break;
        case IN_INCUBATION_STATE:
            in_incubation_state();
            break;
        case AFTER_INCUBATION_STATE:
            after_incubation_state();
            break;
        default:
            iddle_incubation_state();
            break;
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
