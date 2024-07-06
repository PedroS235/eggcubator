/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef EGGCUBATOR_UI_H
#define EGGCUBATOR_UI_H

#include <RotaryEncoder.h>

#include "eggcubator/config/pins.h"
#include "eggcubator/ui/display_manager.h"
#include "eggcubator/ui/language/language.h"
#include "eggcubator/ui/menu.h"

bool is_button_pressed();
void changing_value(menu_item_t *item, float min, float max, float value);

void incubate_menu_callback();
void preheat_menu_callback();
void settings_menu_callback();

// Incubate Menu
void incubate_chicken_menu_callback();
void incubate_quail_menu_callback();
void incubate_duck_menu_callback();
void incubate_turkey_menu_callback();
void incubate_goose_menu_callback();
void incubate_pigeon_menu_callback();

// Preheat Menu
void preheat_manual_menu_callback();
void preheat_chicken_menu_callback();
void preheat_quail_menu_callback();
void preheat_duck_menu_callback();
void preheat_turkey_menu_callback();
void preheat_goose_menu_callback();
void preheat_pigeon_menu_callback();

// Settings Menu
void calibrate_menu_callback();
void eggs_settings_menu_callback();
void save_menu_callback();
void reset_menu_callback();

// Calibrate Menu
void calibrate_temp_offset_menu_callback();
void calibrate_humd_offset_menu_callback();
void calibrate_pid_menu_callback();
void calibrate_motor_menu_callback();

// PID Settings Menu
void pid_p_menu_callback();
void pid_i_menu_callback();
void pid_d_menu_callback();

// Eggs Settings Menu
void settings_chicken_menu_callback();
void settings_quail_menu_callback();
void settings_duck_menu_callback();
void settings_turkey_menu_callback();
void settings_goose_menu_callback();
void settings_pigeon_menu_callback();

// Eggs Config Menu
void config_chicken_menu_callback();
void config_quail_menu_callback();
void config_goose_menu_callback();
void config_duck_menu_callback();
void config_turkey_menu_callback();
void config_pigeon_menu_callback();

// In Incubation Menu
void tune_menu_callback();
void stop_incubation_menu_callback();

// Tune Menu
void tune_target_temp_menu_callback();
void tune_target_humd_menu_callback();
void tune_rot_period_menu_callback();

static RotaryEncoder *encoder = new RotaryEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT);
void encoder_ISR();

class EggCubatorUI {
   private:
    DisplayManager display;

    // Encoder Related
   private:
    bool button_pressed;

    // menus
   private:
    void create_menus();
    void update_menu_items_values();

   private:
    void encoder_update();
    void reset_encoder() { encoder->setPosition(0); }

   private:
    // Main Menu
    void create_main_menu();

    // Incubate Menu
    void create_incubate_menu();

    // Preheat Menu
    void create_preheat_menu();

    // Settings Menu
    void create_settings_menu();

    // Calibrate Menu
    void create_calibrate_menu();

    // PID Settings Menu
    void create_pid_menu();

    // Eggs Settings Menu
    void create_eggs_settings_menu();

    // Eggs Config Menu
    void create_chicken_egg_config_menu();
    void create_quail_egg_config_menu();
    void create_turkey_egg_config_menu();
    void create_goose_egg_config_menu();
    void create_duck_egg_config_menu();
    void create_pigeon_egg_config_menu();

    // In Incubation Menu
    void create_incubation_main_menu();

    // Tune Menu
    void create_tune_menu();

    // Screens
    void info_screen_callback();
    void incubation_info_screen_callback();

   public:
    EggCubatorUI();
    ~EggCubatorUI();
    void render();
};

#endif  // !EGGCUBATOR_UI_H
