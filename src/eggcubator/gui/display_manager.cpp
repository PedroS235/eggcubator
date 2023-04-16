/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/gui/display_manager.h>

#include <cstdint>

#include "clib/u8g2.h"
#include "eggcubator/configuration.h"
#include "eggcubator/gui/icons.h"

DisplayManager::DisplayManager() {
    display = new TYPE_DISPLAY(U8G2_R0, U8X8_PIN_NONE);
    display->begin();
    display->setFontPosTop();
}

void DisplayManager::draw_menu_item_cell(uint8_t x,
                                         uint8_t y,
                                         const char* item_name,
                                         bool select) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    if (select) {
        /* display->setFont(u8g2_font_tenthinguys_t_all); */
        display->setDrawColor(1);
        display->drawRBox(0, y, display->getWidth(), 20, 2);
        display->setDrawColor(0);
        display->drawStr(4, y + 4, item_name);
    } else {
        display->setDrawColor(0);
        display->drawRFrame(0, y, display->getWidth(), 20, 2);
        display->setDrawColor(1);
        display->drawStr(4, y + 4, item_name);
    }
    display->setDrawColor(1);
    display->drawRFrame(0, y, display->getWidth(), 20, 2);
}
void DisplayManager::draw_progress_bar(uint8_t x,
                                       uint8_t y,
                                       uint8_t width,
                                       uint8_t height,
                                       uint8_t percetange) {
    display->drawFrame(x, y, width, height);
    uint8_t w = width * percetange / 100;
    display->drawBox(x, y, w, height);
}

void DisplayManager::draw_temperature(float value, float target) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    display->setCursor(0, 5);
    display->print(value, 1);
    display->drawBitmap(
        2, display->getMaxCharHeight() + 4, 16 / 8, 16, temperature_icon);
    display->setCursor(0, 38);
    display->print(target, 1);
}
void DisplayManager::draw_humidity(float value, float target) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    display->setCursor(display->getWidth() - 25, 5);
    display->print(value, 1);
    display->drawBitmap(display->getWidth() - 22,
                        display->getMaxCharHeight() + 4,
                        16 / 8,
                        16,
                        humidity_icon);
    display->setCursor(display->getWidth() - 25, 38);
    display->print(target, 1);
}
void DisplayManager::draw_time(uint8_t x, uint8_t y, eggcubator::time_t time) {
    display->setFont(u8g2_font_5x8_tf);
    if (time.day > 0) {
        // DD HH::MM
        display->setCursor(x, y);
        display->print(time.day);
        display->print("d ");

        // draw hour
        if (time.hour < 10) display->print("0");
        display->print(time.hour);
        display->print(":");

        // draw minutes
        if (time.minute < 10) display->print("0");
        display->print(time.minute);
    } else {
        // HH::MM::SS
        // draw hours
        display->setCursor(x, y);
        if (time.hour < 10) display->print("0");
        display->print(time.hour);
        display->print(":");

        // draw minutes
        if (time.minute < 10) display->print("0");
        display->print(time.minute);
        display->print(":");

        // draw seconds
        if (time.second < 10) display->print("0");
        display->print(time.second);
    }
}

void DisplayManager::draw_status_screen() {
    display->firstPage();
    do {
        draw_temperature(12.5, 23.5);
        draw_humidity(12.5, 34.5);
    } while (display->nextPage());
}

void DisplayManager::draw_incubation_status_screen() {
    display->firstPage();
    do {
        draw_temperature(12.5, 23.5);
        draw_humidity(12.5, 34.5);
        /* draw_progress_bar(2, 60, display->getWidth() - 4, 4, 30); */
        draw_time(0, 50, {20, 12, 4, 33});

    } while (display->nextPage());
}

void DisplayManager::draw_menu(const char* menu_items[],
                               uint8_t menu_size,
                               uint8_t selected_item) {
    display->firstPage();
    do {
        int y = selected_item > 2 ? -22 * (selected_item - 2) : 0;
        for (int i = 0; i < menu_size; i++) {
            if (i == selected_item) {
                draw_menu_item_cell(0, y, menu_items[i], true);
            } else {
                draw_menu_item_cell(0, y, menu_items[i], false);
            }
            y += 22;
        }
    } while (display->nextPage());
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
