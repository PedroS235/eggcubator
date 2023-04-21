#include <eggcubator/gui/eggcubator_ui.h>

#include "Arduino.h"
#include "eggcubator/gui/menus.h"
#include "eggcubator/pins.h"

EggCubatorUI::EggCubatorUI(RotaryEncoder *encoder_) : display() {
    encoder = encoder_;
    pinMode(PIN_ENCODER_SW, INPUT_PULLUP);
    encoder_pos = encoder->getPosition();
    prev_encoder_pos = encoder_pos;
    button_pressed = false;
    curr_menu_state = INFO_SCREEN;
    set_encoder_bounds(0, -1);
}

void EggCubatorUI::encoder_update() {
    if (encoder->getPosition() > encoder_higher_bound)
        encoder->setPosition(encoder_higher_bound);

    if (encoder->getPosition() < encoder_lower_bound)
        encoder->setPosition(encoder_lower_bound);

    encoder_pos = encoder->getPosition();

    if (digitalRead(PIN_ENCODER_SW) == LOW) {
        if (millis() - last_button_press > 50) {
            tone(PIN_BUZZER, 523, 50);
            button_pressed = true;
            Serial.println("Button pressed!");
        }
        last_button_press = millis();
    } else {
        button_pressed = false;
    }
}

void EggCubatorUI::render() {
    encoder_update();
    switch (curr_menu_state) {
        case MAIN_MENU:
            main_menu_callback();
            break;
        case INFO_SCREEN:
            info_screen_callback();
            break;
        case INCUBATE_MENU:
            incubate_menu_callback();
            break;
        case CALIBRATE_MENU:
            calibrate_menu_callback();
            break;
        case SETTINGS_MENU:
            settings_menu_callback();
            break;
        case PREHEAT_MENU:
            preheat_menu_callback();
            break;
        case PID_MENU:
            pid_menu_callback();
            break;
        case EGGS_SETTINGS_MENU:
            eggs_settings_menu_callback();
            break;
        case INCUBATION_INFO_SCREEN:
            incubation_info_screen_callback();
            break;
        case EGG_CONFIG_MENU:
            egg_config_menu_callback();
            break;
        case TUNE_MENU:
            tune_menu_callback();
            break;
    }
}

void EggCubatorUI::main_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = INFO_SCREEN;
                break;
            case 1:
                // Incubate
                curr_menu_state = INCUBATE_MENU;
                reset_encoder();
                set_encoder_bounds(0, incubate_menu_size - 1);
                break;
            case 2:
                // Preheat
                curr_menu_state = PREHEAT_MENU;
                reset_encoder();
                set_encoder_bounds(0, preheat_menu_size - 1);
                break;
            case 3:
                // Settings
                curr_menu_state = SETTINGS_MENU;
                reset_encoder();
                set_encoder_bounds(0, settings_menu_size - 1);
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(main_menu, main_menu_size, encoder_pos);
}
void EggCubatorUI::incubate_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = MAIN_MENU;
                reset_encoder();
                set_encoder_bounds(0, main_menu_size - 1);
                break;
            case 1:
                // Chicken
                // TODO: Start of incubation
                break;
            case 2:
                // Quail
                // TODO: Start of incubation
                break;
            case 3:
                // Duck
                // TODO: Start of incubation
                break;
            case 4:
                // Turkey
                // TODO: Start of incubation
                break;
            case 5:
                // Goose
                // TODO: Start of incubation
                break;
            case 6:
                // Pigeon
                // TODO: Start of incubation
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(incubate_menu, incubate_menu_size, encoder_pos);
}
void EggCubatorUI::preheat_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = MAIN_MENU;
                reset_encoder();
                set_encoder_bounds(0, main_menu_size - 1);
                break;
            case 1:
                // Manual
                break;
            case 2:
                // Chicken
                // TODO: Start of incubation
                break;
            case 3:
                // Quail
                // TODO: Start of incubation
                break;
            case 4:
                // Duck
                // TODO: Start of incubation
                break;
            case 5:
                // Turkey
                // TODO: Start of incubation
                break;
            case 6:
                // Goose
                // TODO: Start of incubation
                break;
            case 7:
                // Pigeon
                // TODO: Start of incubation
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(preheat_menu, preheat_menu_size, encoder_pos);
}
void EggCubatorUI::eggs_settings_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = SETTINGS_MENU;
                reset_encoder();
                set_encoder_bounds(0, settings_menu_size - 1);
                break;
            case 1:
                // Chicken
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
            case 2:
                // Quail
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
            case 3:
                // Duck
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
            case 4:
                // Turkey
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
            case 5:
                // Goose
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
            case 6:
                // Pigeon
                curr_menu_state = EGG_CONFIG_MENU;
                reset_encoder();
                set_encoder_bounds(0, egg_config_menu_size - 1);
                // TODO: Start of incubation
                break;
        }
        button_pressed = false;
    }
    display.draw_menu(eggs_settings_menu, eggs_settings_menu_size, encoder_pos);
}
void EggCubatorUI::settings_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = MAIN_MENU;
                reset_encoder();
                set_encoder_bounds(0, main_menu_size - 1);
                break;
            case 1:
                // Calibrate
                curr_menu_state = CALIBRATE_MENU;
                reset_encoder();
                set_encoder_bounds(0, calibrate_menu_size - 1);
                break;
            case 2:
                // Eggs settings
                curr_menu_state = EGGS_SETTINGS_MENU;
                reset_encoder();
                set_encoder_bounds(0, eggs_settings_menu_size - 1);
                break;
            case 3:
                // Save
                // TODO(PedroS235): implement the save
                break;
            case 4:
                // reset
                // TODO(PedroS235): implement the reset
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(settings_menu, settings_menu_size, encoder_pos);
}
void EggCubatorUI::calibrate_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = SETTINGS_MENU;
                reset_encoder();
                set_encoder_bounds(0, settings_menu_size - 1);
                break;
            case 1:
                // Temperature
                // TODO(PedroS235): Here we need to draw the screen to change a number
                break;
            case 2:
                // Humidity
                // TODO(PedroS235): Here we need to draw the screen to change a number
                break;
            case 3:
                // PID
                curr_menu_state = PID_MENU;
                reset_encoder();
                set_encoder_bounds(0, pid_menu_size - 1);
                break;
            case 4:
                // Motor duration
                // TODO(PedroS235): Here we need to draw the screen to change a number
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(calibrate_menu, calibrate_menu_size, encoder_pos);
}
void EggCubatorUI::egg_config_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = EGGS_SETTINGS_MENU;
                reset_encoder();
                set_encoder_bounds(0, eggs_settings_menu_size - 1);
                break;
            case 1:
                // Target temp
                // TODO(PedroS235): Implement the change of target Temperature
                break;
            case 2:
                // Target Humd
                // TODO(PedroS235): Implement the change of target Humidity
                break;
            case 3:
                // Period
                // TODO(PedroS235): Implement the change of incubation period
                break;
            case 4:
                // Rot period
                // TODO(PedroS235): Implement the change of the rotation period
                break;
            case 5:
                // Start of rot
                // TODO(PedroS235): Implement the change of the start of rotation
                break;
            case 6:
                // end of rot
                // TODO(PedroS235): Implement the change of the end of rotation
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(egg_config_menu, egg_config_menu_size, encoder_pos);
}
void EggCubatorUI::tune_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = INCUBATION_INFO_SCREEN;
                break;
            case 1:
                // target temp
                // TODO
                break;
            case 2:
                // target humd
                // TODO
                break;
            case 3:
                // Rot period
                // TODO
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(tune_menu, tune_menu_size, encoder_pos);
    display.draw_incubation_status_screen();
}
void EggCubatorUI::pid_menu_callback() {
    if (button_pressed) {
        switch (encoder_pos) {
            case 0:
                // Go back
                curr_menu_state = CALIBRATE_MENU;
                set_encoder_bounds(0, calibrate_menu_size - 1);
                reset_encoder();
                break;
            case 1:
                // KP
                // TODO
                break;
            case 2:
                // KI
                // TODO
                break;
            case 3:
                // KD
                // TODO
                break;
        }
        button_pressed = false;
    }

    display.draw_menu(pid_menu, pid_menu_size, encoder_pos);
}

void EggCubatorUI::info_screen_callback() {
    if (button_pressed) {
        curr_menu_state = MAIN_MENU;
        button_pressed = false;
        set_encoder_bounds(0, main_menu_size - 1);
        reset_encoder();
    }
    display.draw_status_screen();
}

void EggCubatorUI::incubation_info_screen_callback() {
    if (button_pressed) {
        curr_menu_state = TUNE_MENU;
        button_pressed = false;
        reset_encoder();
    }
    display.draw_incubation_status_screen();
}
