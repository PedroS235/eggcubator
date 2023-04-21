/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EGGCUBATOR_UI_H
#define EGGCUBATOR_UI_H

#include <RotaryEncoder.h>

#include "eggcubator/gui/display_manager.h"
#include "eggcubator/pins.h"

// Menus States

#define MAIN_MENU 0
#define INCUBATE_MENU 1
#define PREHEAT_MENU 2
#define EGGS_SETTINGS_MENU 3
#define SETTINGS_MENU 4
#define CALIBRATE_MENU 5
#define EGG_CONFIG_MENU 6
#define TUNE_MENU 7
#define PID_MENU 8
#define INFO_SCREEN 9
#define INCUBATION_INFO_SCREEN 10

class EggCubatorUI {
   private:
    long encoder_pos;
    long prev_encoder_pos;
    uint8_t curr_menu_state;
    char **curr_menu;
    bool button_pressed;
    unsigned long last_button_press;
    DisplayManager display;
    RotaryEncoder *encoder;
    long encoder_lower_bound, encoder_higher_bound;

   private:
    void encoder_update();
    void reset_encoder() {
        encoder->setPosition(0);
        encoder_pos = 0;
    }
    void set_encoder_bounds(long l, long h) {
        encoder_lower_bound = l;
        encoder_higher_bound = h;
    }

    // Menus states methods
   private:
    void main_menu_callback();
    void incubate_menu_callback();
    void preheat_menu_callback();
    void eggs_settings_menu_callback();
    void settings_menu_callback();
    void calibrate_menu_callback();
    void egg_config_menu_callback();
    void tune_menu_callback();
    void pid_menu_callback();
    void info_screen_callback();
    void incubation_info_screen_callback();

   public:
    EggCubatorUI(RotaryEncoder *encoder_);
    void render();
};

#endif  // !EGGCUBATOR_UI_H
