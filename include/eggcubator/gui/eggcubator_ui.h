/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EGGCUBATOR_UI_H
#define EGGCUBATOR_UI_H

#include <RotaryEncoder.h>

#include "eggcubator/gui/display_manager.h"
#include "eggcubator/gui/language/language.h"
#include "eggcubator/gui/menu.h"
#include "eggcubator/pins.h"

class EggCubatorUI {
   private:
    DisplayManager display;

    // Encoder Related
   private:
    RotaryEncoder *encoder;
    bool button_pressed;
    unsigned long last_button_press;
    long encoder_pos;
    float encoder_res = 1;

    // menus
   private:
    void create_menus();

   private:
    void encoder_update();
    void reset_encoder() {
        encoder->setPosition(0);
        encoder_pos = 0;
    }

    // Main Menu
   private:
    void create_main_menu();
    static void incubate_menu_callback();
    static void preheat_menu_callback();
    static void settings_menu_callback();

    // Incubate Menu
   private:
    void create_incubate_menu();
    static void incubate_chicken_menu_callback();
    static void incubate_quail_menu_callback();
    static void incubate_duck_menu_callback();
    static void incubate_turkey_menu_callback();
    static void incubate_goose_menu_callback();
    static void incubate_pigeon_menu_callback();

    // Preheat Menu
   private:
    void create_preheat_menu();
    static void preheat_manual_menu_callback();
    static void preheat_chicken_menu_callback();
    static void preheat_quail_menu_callback();
    static void preheat_duck_menu_callback();
    static void preheat_turkey_menu_callback();
    static void preheat_goose_menu_callback();
    static void preheat_pigeon_menu_callback();

    // Settings Menu
   private:
    void create_settings_menu();
    static void calibrate_menu_callback();
    static void eggs_settings_menu_callback();
    static void save_menu_callback();
    static void reset_menu_callback();

    // Calibrate Menu
   private:
    void create_calibrate_menu();
    static void calibrate_temp_menu_callback();
    static void calibrate_humd_menu_callback();
    static void calibrate_pid_menu_callback();
    static void calibrate_motor_menu_callback();

    // PID Settings Menu
   private:
    void create_pid_menu();
    static void pid_p_menu_callback();
    static void pid_i_menu_callback();
    static void pid_d_menu_callback();

    // Eggs Settings Menu
   private:
    void create_eggs_settings_menu();
    static void settings_chicken_menu_callback();
    static void settings_quail_menu_callback();
    static void settings_duck_menu_callback();
    static void settings_turkey_menu_callback();
    static void settings_goose_menu_callback();
    static void settings_pigeon_menu_callback();

    // Eggs Config Menu
   private:
    void create_egg_config_menu();
    static void config_chicken_menu_callback();
    static void config_quail_menu_callback();
    static void config_goose_menu_callback();
    static void config_duck_menu_callback();
    static void config_turkey_menu_callback();
    static void config_pigeon_menu_callback();

    // In Incubation Menu
   private:
    void create_incubation_main_menu();
    static void tune_menu_callback();
    static void stop_incubation_menu_callback();

    // Tune Menu
   private:
    void create_tune_menu();
    static void tune_target_temp_menu_callback();
    static void tune_target_humd_menu_callback();
    static void tune_rot_period_menu_callback();

    // Screens
   private:
    void info_screen_callback();
    void incubation_info_screen_callback();
    static void change_value_screen_callback();

   public:
    EggCubatorUI(RotaryEncoder *encoder_);
    ~EggCubatorUI();
    void render();
};

#endif  // !EGGCUBATOR_UI_H
