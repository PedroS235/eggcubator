/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#include <eggcubator/gui/display_manager.h>

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

void DisplayManager::draw_temperature(uint8_t x, uint8_t y, float value, float target) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    display->setCursor(x, y);
    display->print(value, 1);
    display->drawBitmap(
        x + 2, y + display->getMaxCharHeight() + 4, 16 / 8, 16, temperature_icon);
    display->setCursor(x, y + 38);
    display->print(target, 1);
}

void DisplayManager::draw_humidity(uint8_t x, uint8_t y, float value, float target) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    display->setCursor(x, y);
    display->print(value, 1);
    display->drawBitmap(
        x + 2, y + display->getMaxCharHeight() + 4, 16 / 8, 16, temperature_icon);
    display->setCursor(x, y + 38);
    display->print(target, 1);
}

void DisplayManager::draw_time(uint8_t x, uint8_t y, eggcubator::time_t time) {
    // Time format (Dd) HH::MM
    display->setFont(u8g2_font_5x8_tf);
    display->setCursor(x, y);
    if (time.day > 0) {
        // DD HH::MM
        display->print(time.day);
        display->print("d ");
    }
    // HH
    if (time.hour < 10) display->print("0");
    display->print(time.hour);
    display->print(":");

    // MM
    if (time.minute < 10) display->print("0");
    display->print(time.minute);
}

void DisplayManager::draw_title(const char* title) {
    display->setFont(u8g2_font_tenthinnerguys_tr);
    display->drawStr(
        display->getWidth() / 2 - display->getStrWidth(title) / 2, 0, title);
    display->drawHLine(0, display->getMaxCharHeight() + 1, display->getWidth());
}

void DisplayManager::draw_status_screen() {
    display->firstPage();
    do {
        draw_temperature(0, 0, 12.5, 23.5);
        draw_humidity(display->getWidth() - 25, 0, 12.5, 34.5);
    } while (display->nextPage());
}

void DisplayManager::draw_incubation_status_screen() {
    display->firstPage();
    do {
        draw_temperature(0, 0, 12.5, 23.5);
        draw_humidity(display->getWidth() - 25, 0, 12.5, 34.5);
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

void DisplayManager::draw_number_change(const char* title, float number) {
    display->firstPage();
    do {
        draw_title(title);
        int x, y;
        x = display->getWidth() / 2 - 10;
        y = display->getMaxCharHeight() + 1 +
            (display->getHeight() - display->getMaxCharHeight() + 1) / 2 -
            display->getMaxCharHeight() / 2;
        display->setCursor(x, y);
        display->print(number, 1);
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
