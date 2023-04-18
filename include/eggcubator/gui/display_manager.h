/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <U8g2lib.h>
#include <eggcubator/configuration.h>
#include <eggcubator/timer.h>

class DisplayManager {
    TYPE_DISPLAY* display;

   private:
    void draw_menu_item_cell(uint8_t x, uint8_t y, const char* item_name, bool select);
    void draw_progress_bar(uint8_t x,
                           uint8_t y,
                           uint8_t width,
                           uint8_t height,
                           uint8_t percetange);
    void draw_temperature(uint8_t x, uint8_t y, float value, float target);
    void draw_humidity(uint8_t x, uint8_t y, float value, float target);
    void draw_time(uint8_t x, uint8_t y, eggcubator::time_t time);

   public:
    DisplayManager();
    /**
     * @brief Draws the basic information when in iddle, such as:
     *  + temperature
     *  + humidity
     */
    void draw_status_screen();

    /**
     * @brief Draws the information about the current incubation in place, such
     * as:
     *  + temperature
     *  + humidity
     *  + incubation time
     *  + progress bar
     */
    void draw_incubation_status_screen();

    /**
     * @brief Draws a menu based on the items passed as a parameter. It also
     * highlights the selected item.
     * @param menu_items: menu items to be displayed
     * @param menu_size: the total number of menus
     * @param selected_item: index of the selected item (0-menu_size)
     */
    void draw_menu(const char* menu_items[], uint8_t menu_size, uint8_t selected_item);
};

#endif  // !DISPLAY_MANAGER_H

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
