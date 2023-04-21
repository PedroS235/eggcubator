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

class EggCubatorUI {
   private:
    long encoder_pos;
    long prev_encoder_pos;
    char **curr_menu;
    bool button_pressed;
    unsigned long last_button_press;
    DisplayManager display;
    RotaryEncoder *encoder;

   private:
    void encoder_update();

   public:
    EggCubatorUI(RotaryEncoder *encoder_);
    void render();
};

#endif  // !EGGCUBATOR_UI_H
