/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <U8g2lib.h>
#include <eggcubator/config/configuration.h>
#include <eggcubator/core/timer.h>

#include "eggcubator/ui/menu.h"

class DisplayManager {
    UI_OLED_TYPE* display;

   private:
    void draw_text_item(uint8_t x, uint8_t y, const char* item_name, bool select);
    void draw_value_item(uint8_t x,
                         uint8_t y,
                         const char* item_name,
                         bool select,
                         float value,
                         uint8_t precision);
    void draw_progress_bar(uint8_t x,
                           uint8_t y,
                           uint8_t width,
                           uint8_t height,
                           uint8_t percetange);
    void draw_temperature(uint8_t x, uint8_t y, float value, float target);
    void draw_humidity(uint8_t x, uint8_t y, float value, float target);
    void draw_time(uint8_t x, uint8_t y, eggcubator::time_t time);
    void draw_title(const char* title);

   public:
    DisplayManager();
    /**
     * @brief Draws the basic information when in iddle, such as:
     *  + temperature
     *  + humidity
     */
    void draw_status_screen(float temp,
                            float target_temp,
                            float humd,
                            float target_humd);

    /**
     * @brief Draws the information about the current incubation in place, such
     * as:
     *  + temperature
     *  + humidity
     *  + incubation time
     *  + progress bar
     */
    void draw_incubation_status_screen(float temp,
                                       float target_temp,
                                       float humd,
                                       float target_humd,
                                       eggcubator::time_t curr_time,
                                       long total_days);

    /**
     * @brief Draws a menu based on the items passed as a parameter. It also
     * highlights the selected item.
     */
    void draw_menu(Menu* menu);

    void draw_boot_screen(const char* text);
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
