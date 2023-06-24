#include <eggcubator/gui/eggcubator_ui.h>

#include "Arduino.h"
#include "HardwareSerial.h"
#include "eggcubator/egg.h"
#include "eggcubator/gui/language/language.h"
#include "eggcubator/gui/menu.h"
#include "eggcubator/incubation_routine.h"
#include "eggcubator/pins.h"

Menu *curr_menu = NULL;
Menu *main_menu = NULL;
Menu *incubate_menu = NULL;
Menu *preheat_menu = NULL;
Menu *settings_menu = NULL;

Menu *incubation_main_menu = NULL;

Menu *eggs_settings_menu = NULL;
Menu *egg_config_menu = NULL;

Menu *calibrate_menu = NULL;
Menu *pid_menu = NULL;

Menu *info_screen = NULL;
Menu *incubation_info_screen = NULL;
Menu *tune_menu = NULL;

EggCubatorUI::EggCubatorUI(RotaryEncoder *encoder_) : display() {
    encoder = encoder_;
    pinMode(PIN_ENCODER_SW, INPUT_PULLUP);
    encoder_pos = encoder->getPosition();
    button_pressed = false;
    curr_menu = NULL;
    create_menus();
}

EggCubatorUI::~EggCubatorUI() {
    delete main_menu;
    delete incubate_menu;
    delete preheat_menu;
    delete settings_menu;
    delete incubation_main_menu;
    delete eggs_settings_menu;
    delete egg_config_menu;
    delete calibrate_menu;
    delete pid_menu;
    delete info_screen;
    delete incubation_info_screen;
    delete tune_menu;
}

void EggCubatorUI::encoder_update() {
    if (curr_menu != NULL) {
        if (encoder->getPosition() > curr_menu->size() - 1)
            encoder->setPosition(curr_menu->size() - 1);

        if (encoder->getPosition() < 0) encoder->setPosition(0);
        encoder_pos = encoder->getPosition();
        curr_menu->move_selection_w_encoder(encoder_pos);
    }

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
    if (curr_menu == NULL) {
        extern IncubationRoutine *routine;
        if (routine->in_incubation())
            incubation_info_screen_callback();
        else
            info_screen_callback();
    } else {
        display.draw_menu(curr_menu);
        if (button_pressed) {
            if (curr_menu->selected_item().callback != NULL) {
                curr_menu->selected_item().callback();
            } else {
                curr_menu = curr_menu->parent_menu();
            }
            encoder->setPosition(0);
            encoder_pos = 0;
            button_pressed = false;
        }
    }
}

void EggCubatorUI::info_screen_callback() {
    if (button_pressed) {
        curr_menu = main_menu;
        button_pressed = false;
        reset_encoder();
    }
    extern float curr_temp;
    extern float temp_target;
    extern float curr_humd;
    extern float humd_target;
    display.draw_status_screen(curr_temp, temp_target, curr_humd, humd_target);
}

void EggCubatorUI::incubation_info_screen_callback() {
    if (button_pressed) {
        curr_menu = incubation_main_menu;
        button_pressed = false;
        reset_encoder();
    }
    extern IncubationRoutine *routine;
    extern float curr_temp;
    extern float temp_target;
    extern float curr_humd;
    extern float humd_target;

    if (!routine->in_incubation()) {
        curr_menu = NULL;
    }

    display.draw_incubation_status_screen(
        curr_temp,
        temp_target,
        curr_humd,
        humd_target,
        routine->get_curr_time().get_time_t(),
        routine->curr_egg_in_incubation().incubation_days);
}

// -----------------------------------------------------------------------------
// -----------------------------| Menu Definitions |----------------------------
// -----------------------------------------------------------------------------

// --------------------------------| Main Menu |--------------------------------

void EggCubatorUI::create_main_menu() {
    menu_item_t *main_menu_items = new menu_item_t[4];
    main_menu_items[0] = {GO_BACK_STR, NULL, 0};
    main_menu_items[1] = {INCUBATE_STR, incubate_menu_callback, 0};
    main_menu_items[2] = {PREHEAT_STR, preheat_menu_callback, 0};
    main_menu_items[3] = {SETTINGS_STR, settings_menu_callback, 0};

    main_menu = new Menu(main_menu_items, NULL, 4);
}

void EggCubatorUI::incubate_menu_callback() { curr_menu = incubate_menu; }
void EggCubatorUI::preheat_menu_callback() { curr_menu = preheat_menu; }
void EggCubatorUI::settings_menu_callback() { curr_menu = settings_menu; }

// -----------------------------| Incubate Menu |-------------------------------

void EggCubatorUI::create_incubate_menu() {
    menu_item_t *incubate_menu_items = new menu_item_t[7];

    incubate_menu_items[0] = {GO_BACK_STR, NULL, 0};
    incubate_menu_items[1] = {CHICKEN_STR, incubate_chicken_menu_callback, 0};
    incubate_menu_items[2] = {QUAIL_STR, incubate_quail_menu_callback, 0};
    incubate_menu_items[3] = {DUCK_STR, incubate_duck_menu_callback, 0};
    incubate_menu_items[4] = {TURKEY_STR, incubate_turkey_menu_callback, 0};
    incubate_menu_items[5] = {GOOSE_STR, incubate_goose_menu_callback, 0};
    incubate_menu_items[6] = {PIGEON_STR, incubate_pigeon_menu_callback, 0};

    incubate_menu = new Menu(incubate_menu_items, main_menu, 7);
}

void EggCubatorUI::incubate_chicken_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&chicken_egg);
    curr_menu = NULL;
}
void EggCubatorUI::incubate_quail_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&quail_egg);
    curr_menu = NULL;
}
void EggCubatorUI::incubate_duck_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&duck_egg);
    curr_menu = NULL;
}
void EggCubatorUI::incubate_turkey_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&turkey_egg);
    curr_menu = NULL;
}
void EggCubatorUI::incubate_goose_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&goose_egg);
    curr_menu = NULL;
}
void EggCubatorUI::incubate_pigeon_menu_callback() {
    extern IncubationRoutine *routine;
    routine->start_incubation(&pigeon_egg);
    curr_menu = NULL;
}

// ------------------------------| Preheat Menu |-------------------------------

void EggCubatorUI::create_preheat_menu() {
    menu_item_t *preheat_menu_items = new menu_item_t[8];

    preheat_menu_items[0] = {GO_BACK_STR, NULL, 0};
    preheat_menu_items[1] = {MANUAL_STR, NULL, 0};
    preheat_menu_items[2] = {CHICKEN_STR, preheat_chicken_menu_callback, 0};
    preheat_menu_items[3] = {QUAIL_STR, preheat_quail_menu_callback, 0};
    preheat_menu_items[4] = {DUCK_STR, preheat_duck_menu_callback, 0};
    preheat_menu_items[5] = {TURKEY_STR, preheat_turkey_menu_callback, 0};
    preheat_menu_items[6] = {GOOSE_STR, preheat_goose_menu_callback, 0};
    preheat_menu_items[7] = {PIGEON_STR, preheat_pigeon_menu_callback, 0};

    preheat_menu = new Menu(preheat_menu_items, main_menu, 8);
}

void EggCubatorUI::preheat_chicken_menu_callback() {}
void EggCubatorUI::preheat_quail_menu_callback() {}
void EggCubatorUI::preheat_duck_menu_callback() {}
void EggCubatorUI::preheat_turkey_menu_callback() {}
void EggCubatorUI::preheat_goose_menu_callback() {}
void EggCubatorUI::preheat_pigeon_menu_callback() {}

// ------------------------------| Settings Menu |------------------------------

void EggCubatorUI::create_settings_menu() {
    menu_item_t *settings_menu_items = new menu_item_t[5];

    settings_menu_items[0] = {GO_BACK_STR, NULL, 0};
    settings_menu_items[1] = {CALIBRATE_STR, calibrate_menu_callback, 0};
    settings_menu_items[2] = {EGGS_SETTINGS_STR, eggs_settings_menu_callback, 0};
    settings_menu_items[3] = {SAVE_STR, save_menu_callback, 0};
    settings_menu_items[4] = {RESET_STR, reset_menu_callback, 0};

    settings_menu = new Menu(settings_menu_items, main_menu, 5);
}

void EggCubatorUI::calibrate_menu_callback() { curr_menu = calibrate_menu; }
void EggCubatorUI::eggs_settings_menu_callback() { curr_menu = eggs_settings_menu; }
void EggCubatorUI::save_menu_callback() {}
void EggCubatorUI::reset_menu_callback() {}

// -----------------------------| Calibrate Menu |------------------------------

void EggCubatorUI::create_calibrate_menu() {
    menu_item_t *calibrate_menu_items = new menu_item_t[5];
    calibrate_menu_items[0] = {GO_BACK_STR, NULL, 0};
    calibrate_menu_items[1] = {TEMEPERATURE_STR, calibrate_temp_menu_callback, 0};
    calibrate_menu_items[2] = {HUMIDITY_STR, calibrate_humd_menu_callback, 0};
    calibrate_menu_items[3] = {"PID", calibrate_pid_menu_callback, 0};
    calibrate_menu_items[4] = {MOTOR_DURATION_STR, calibrate_motor_menu_callback, 0};

    calibrate_menu = new Menu(calibrate_menu_items, settings_menu, 5);
}

void EggCubatorUI::calibrate_temp_menu_callback() {}
void EggCubatorUI::calibrate_humd_menu_callback() {}
void EggCubatorUI::calibrate_pid_menu_callback() { curr_menu = pid_menu; }
void EggCubatorUI::calibrate_motor_menu_callback() {}

// --------------------------------| PID Menu |---------------------------------

void EggCubatorUI::create_pid_menu() {
    menu_item_t *pid_menu_items = new menu_item_t[4];
    pid_menu_items[0] = {GO_BACK_STR, NULL, 0};
    pid_menu_items[1] = {"kp", pid_p_menu_callback, 0};
    pid_menu_items[2] = {"ki", pid_i_menu_callback, 0};
    pid_menu_items[3] = {"kd", pid_d_menu_callback, 0};

    pid_menu = new Menu(pid_menu_items, calibrate_menu, 4);
}

void EggCubatorUI::pid_p_menu_callback() {}
void EggCubatorUI::pid_i_menu_callback() {}
void EggCubatorUI::pid_d_menu_callback() {}

// ----------------------------| Eggs Settings Menu |---------------------------

void EggCubatorUI::create_eggs_settings_menu() {
    menu_item_t *eggs_settings_menu_items = new menu_item_t[7];

    eggs_settings_menu_items[0] = {GO_BACK_STR, NULL, 0};
    eggs_settings_menu_items[1] = {CHICKEN_STR, settings_chicken_menu_callback, 0};
    eggs_settings_menu_items[2] = {QUAIL_STR, settings_quail_menu_callback, 0};
    eggs_settings_menu_items[3] = {DUCK_STR, settings_duck_menu_callback, 0};
    eggs_settings_menu_items[4] = {TURKEY_STR, settings_turkey_menu_callback, 0};
    eggs_settings_menu_items[5] = {GOOSE_STR, settings_goose_menu_callback, 0};
    eggs_settings_menu_items[6] = {PIGEON_STR, settings_pigeon_menu_callback, 0};

    eggs_settings_menu = new Menu(eggs_settings_menu_items, settings_menu, 7);
}

void EggCubatorUI::settings_chicken_menu_callback() {}
void EggCubatorUI::settings_quail_menu_callback() {}
void EggCubatorUI::settings_duck_menu_callback() {}
void EggCubatorUI::settings_turkey_menu_callback() {}
void EggCubatorUI::settings_goose_menu_callback() {}
void EggCubatorUI::settings_pigeon_menu_callback() {}

// -----------------------------| Egg Config Menu |-----------------------------

void EggCubatorUI::create_egg_config_menu() {
    menu_item_t *egg_config_menu_items = new menu_item_t[7];

    // TODO: Missing callbacks declarations

    egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0};
    egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, 0};
    egg_config_menu_items[2] = {TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, 0};
    egg_config_menu_items[3] = {PERIOD_STR, NULL, 0};
    egg_config_menu_items[4] = {ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0};
    egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0};
    egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0};

    egg_config_menu = new Menu(egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::config_chicken_menu_callback() {}
void EggCubatorUI::config_quail_menu_callback() {}
void EggCubatorUI::config_goose_menu_callback() {}
void EggCubatorUI::config_duck_menu_callback() {}
void EggCubatorUI::config_turkey_menu_callback() {}
void EggCubatorUI::config_pigeon_menu_callback() {}

// ----------------------------| In Incubation Menu |---------------------------

void EggCubatorUI::create_incubation_main_menu() {
    menu_item_t *incubation_main_menu_items = new menu_item_t[3];
    incubation_main_menu_items[0] = {GO_BACK_STR, NULL, 0};
    incubation_main_menu_items[1] = {TUNE_STR, tune_menu_callback, 0};
    incubation_main_menu_items[2] = {
        STOP_INCUBATION_STR, stop_incubation_menu_callback, 0};

    incubation_main_menu = new Menu(incubation_main_menu_items, NULL, 3);
}

void EggCubatorUI::tune_menu_callback() { curr_menu = tune_menu; }
void EggCubatorUI::stop_incubation_menu_callback() {
    extern IncubationRoutine *routine;
    routine->stop_incubation();
    curr_menu = NULL;
}

// --------------------------------| Tune Menu |--------------------------------

void EggCubatorUI::create_tune_menu() {
    menu_item_t *tune_menu_items = new menu_item_t[4];
    tune_menu_items[0] = {GO_BACK_STR, NULL, 0};
    tune_menu_items[1] = {TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, 0};
    tune_menu_items[2] = {TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, 0};
    tune_menu_items[3] = {ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0};

    tune_menu = new Menu(tune_menu_items, incubation_main_menu, 4);
}

void EggCubatorUI::tune_target_temp_menu_callback() {}
void EggCubatorUI::tune_target_humd_menu_callback() {}
void EggCubatorUI::tune_rot_period_menu_callback() {}

void EggCubatorUI::create_menus() {
    create_main_menu();
    create_pid_menu();
    create_incubate_menu();
    create_settings_menu();
    create_egg_config_menu();
    create_preheat_menu();
    create_incubation_main_menu();
    create_eggs_settings_menu();
    create_calibrate_menu();
    create_tune_menu();
}

void EggCubatorUI::change_value_screen_callback() {}
