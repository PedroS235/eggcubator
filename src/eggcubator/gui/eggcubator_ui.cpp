#include <eggcubator/gui/eggcubator_ui.h>

#include "Arduino.h"
#include "RotaryEncoder.h"
#include "eggcubator/egg.h"
#include "eggcubator/gui/menu.h"
#include "eggcubator/incubation_routine.h"
#include "eggcubator/module/eeprom_manager.h"
#include "eggcubator/module/thermostat.h"
#include "eggcubator/pins.h"

static Menu *curr_menu = NULL;

static Menu *main_menu = NULL;
static menu_item_t *main_menu_items = new menu_item_t[4];

static Menu *incubate_menu = NULL;
static menu_item_t *incubate_menu_items = new menu_item_t[7];

static Menu *preheat_menu = NULL;
static menu_item_t *preheat_menu_items = new menu_item_t[8];

static Menu *settings_menu = NULL;
static menu_item_t *settings_menu_items = new menu_item_t[5];

static Menu *incubation_main_menu = NULL;
static menu_item_t *incubation_main_menu_items = new menu_item_t[4];

static Menu *eggs_settings_menu = NULL;
static menu_item_t *eggs_settings_menu_items = new menu_item_t[7];

static Menu *egg_config_menu = NULL;
static menu_item_t *chicken_egg_config_menu_items = new menu_item_t[7];
static menu_item_t *quail_egg_config_menu_items = new menu_item_t[7];
static menu_item_t *goose_egg_config_menu_items = new menu_item_t[7];
static menu_item_t *turkey_egg_config_menu_items = new menu_item_t[7];
static menu_item_t *pigeon_egg_config_menu_items = new menu_item_t[7];
static menu_item_t *duck_egg_config_menu_items = new menu_item_t[7];

static Menu *calibrate_menu = NULL;
static menu_item_t *calibrate_menu_items = new menu_item_t[5];
static Menu *pid_menu = NULL;
static menu_item_t *pid_menu_items = new menu_item_t[4];

static Menu *tune_menu = NULL;
static menu_item_t *tune_menu_items = new menu_item_t[4];

static Menu *info_screen = NULL;
static Menu *incubation_info_screen = NULL;

static void (*selected_callback)(void);

static unsigned long last_button_press = 0;
static int prev_encoder_pos = 0;
static float step = 1.0;

extern float temp_target;
extern float humd_target;
extern float curr_temp;
extern float curr_humd;
extern egg_t selected_egg;
extern IncubationRoutine *routine;
extern Thermostat *thermostat;
extern RotaryEncoder *encoder;

bool is_button_pressed() {
    bool pressed = false;
    if (digitalRead(PIN_ENCODER_SW) == LOW) {
        if (millis() - last_button_press > 50) {
            tone(PIN_BUZZER, 523, 50);
            pressed = true;
        }
        last_button_press = millis();
    }
    return pressed;
}

void changing_value(menu_item_t *item, float min, float max, float value) {
    item->value = value;
    if (is_button_pressed()) {
        item->precision = (item->precision + 1) % 3;
        step /= 10;
    }

    int encoder_pos = encoder->getPosition();
    item->value += (encoder_pos - prev_encoder_pos) * step;
    encoder->setPosition(prev_encoder_pos);

    if (item->precision == 0) {
        selected_callback = NULL;
    }
}

EggCubatorUI::EggCubatorUI(RotaryEncoder *encoder_) : display() {
    encoder = encoder_;
    pinMode(PIN_ENCODER_SW, INPUT_PULLUP);
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

    delete[] main_menu_items;
    delete[] incubate_menu_items;
    delete[] preheat_menu_items;
    delete[] settings_menu_items;
    delete[] incubation_main_menu_items;
    delete[] eggs_settings_menu_items;
    delete[] calibrate_menu_items;
    delete[] pid_menu_items;
    delete[] tune_menu_items;
    delete[] incubation_info_screen;
}

void EggCubatorUI::encoder_update() {
    if (curr_menu != NULL) {
        if (encoder->getPosition() > curr_menu->size() - 1)
            encoder->setPosition(curr_menu->size() - 1);

        if (encoder->getPosition() < 0) reset_encoder();
        curr_menu->move_selection_w_encoder(encoder->getPosition());
    }

    if (is_button_pressed())
        button_pressed = true;
    else
        button_pressed = false;
}

void EggCubatorUI::render() {
    if (selected_callback == NULL) {
        encoder_update();
        if (curr_menu == NULL) {
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
                if (curr_menu != NULL) {
                    if (!curr_menu->selected_item().is_value) reset_encoder();
                }
                button_pressed = false;
            }
        }
    } else {
        selected_callback();
        display.draw_menu(curr_menu);
    }
}

void EggCubatorUI::info_screen_callback() {
    if (button_pressed) {
        curr_menu = main_menu;
        button_pressed = false;
        reset_encoder();
    }
    display.draw_status_screen(curr_temp, temp_target, curr_humd, humd_target);
}

void EggCubatorUI::incubation_info_screen_callback() {
    if (button_pressed) {
        curr_menu = incubation_main_menu;
        button_pressed = false;
        reset_encoder();
    }

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
    main_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    main_menu_items[1] = {
        INCUBATE_STR,
        incubate_menu_callback,
        0,
        false,
    };
    main_menu_items[2] = {PREHEAT_STR, preheat_menu_callback, 0, false, 0};
    main_menu_items[3] = {SETTINGS_STR, settings_menu_callback, 0, false, 0};

    main_menu = new Menu(main_menu_items, NULL, 4);
}

void incubate_menu_callback() { curr_menu = incubate_menu; }
void preheat_menu_callback() { curr_menu = preheat_menu; }
void settings_menu_callback() { curr_menu = settings_menu; }

// -----------------------------| Incubate Menu |-------------------------------

void EggCubatorUI::create_incubate_menu() {
    incubate_menu_items[0] = {GO_BACK_STR, NULL, 0};
    incubate_menu_items[1] = {CHICKEN_STR, incubate_chicken_menu_callback, 0, false, 0};
    incubate_menu_items[2] = {QUAIL_STR, incubate_quail_menu_callback, 0, false, 0};
    incubate_menu_items[3] = {DUCK_STR, incubate_duck_menu_callback, 0, false, 0};
    incubate_menu_items[4] = {TURKEY_STR, incubate_turkey_menu_callback, 0, false, 0};
    incubate_menu_items[5] = {GOOSE_STR, incubate_goose_menu_callback, 0, false, 0};
    incubate_menu_items[6] = {PIGEON_STR, incubate_pigeon_menu_callback, 0, false, 0};

    incubate_menu = new Menu(incubate_menu_items, main_menu, 7);
}

void incubate_chicken_menu_callback() {
    routine->start_incubation(get_chicken_egg_config());
    curr_menu = NULL;
}
void incubate_quail_menu_callback() {
    routine->start_incubation(get_quail_egg_config());
    curr_menu = NULL;
}
void incubate_duck_menu_callback() {
    routine->start_incubation(get_duck_egg_config());
    curr_menu = NULL;
}
void incubate_turkey_menu_callback() {
    routine->start_incubation(get_turkey_egg_config());
    curr_menu = NULL;
}
void incubate_goose_menu_callback() {
    routine->start_incubation(get_goose_egg_config());
    curr_menu = NULL;
}
void incubate_pigeon_menu_callback() {
    routine->start_incubation(get_pigeon_egg_config());
    curr_menu = NULL;
}

// ------------------------------| Preheat Menu |-------------------------------

void EggCubatorUI::create_preheat_menu() {
    preheat_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    preheat_menu_items[1] = {
        MANUAL_STR, preheat_manual_menu_callback, temp_target, true, 0};
    preheat_menu_items[2] = {CHICKEN_STR, preheat_chicken_menu_callback, 0, false, 0};
    preheat_menu_items[3] = {QUAIL_STR, preheat_quail_menu_callback, 0, false, 0};
    preheat_menu_items[4] = {DUCK_STR, preheat_duck_menu_callback, 0, false, 0};
    preheat_menu_items[5] = {TURKEY_STR, preheat_turkey_menu_callback, 0, false, 0};
    preheat_menu_items[6] = {GOOSE_STR, preheat_goose_menu_callback, 0, false, 0};
    preheat_menu_items[7] = {PIGEON_STR, preheat_pigeon_menu_callback, 0, false, 0};

    preheat_menu = new Menu(preheat_menu_items, main_menu, 8);
}

void preheat_manual_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = preheat_manual_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    changing_value(item, 0, 50, temp_target);
    temp_target = item->value;
}

void preheat_chicken_menu_callback() {
    egg_t egg_config = *get_chicken_egg_config();
    eeprom_read_chicken_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}
void preheat_quail_menu_callback() {
    egg_t egg_config = *get_quail_egg_config();
    eeprom_read_quail_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}
void preheat_duck_menu_callback() {
    egg_t egg_config = *get_duck_egg_config();
    eeprom_read_duck_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}
void preheat_turkey_menu_callback() {
    egg_t egg_config = *get_turkey_egg_config();
    eeprom_read_turkey_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}
void preheat_goose_menu_callback() {
    egg_t egg_config = *get_goose_egg_config();
    eeprom_read_goose_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}
void preheat_pigeon_menu_callback() {
    egg_t egg_config = *get_pigeon_egg_config();
    eeprom_read_pigeon_egg_config(&egg_config);
    temp_target = egg_config.target_temp;
}

// ------------------------------| Settings Menu |------------------------------

void EggCubatorUI::create_settings_menu() {
    settings_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    settings_menu_items[1] = {CALIBRATE_STR, calibrate_menu_callback, 0, false, 0};
    /* settings_menu_items[2] = { */
    /*     EGGS_SETTINGS_STR, eggs_settings_menu_callback, 0, false, 0}; */
    settings_menu_items[2] = {SAVE_STR, save_menu_callback, 0, false, 0};
    settings_menu_items[3] = {RESET_STR, reset_menu_callback, 0, false, 0};

    settings_menu = new Menu(settings_menu_items, main_menu, 4);
}

void calibrate_menu_callback() { curr_menu = calibrate_menu; }
void eggs_settings_menu_callback() { curr_menu = eggs_settings_menu; }
// TODO: Save to eeprom
void save_menu_callback() {}
void reset_menu_callback() {
    eeprom_reset();
    // Adding a small delay to allow the user to see the reset message
    delay(100);
}

// -----------------------------| Calibrate Menu |------------------------------

void EggCubatorUI::create_calibrate_menu() {
    calibrate_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    calibrate_menu_items[1] = {TEMPERATURE_OFFSET_STR,
                               calibrate_temp_offset_menu_callback,
                               thermostat->get_temp_correction(),
                               true,
                               0};
    calibrate_menu_items[2] = {
        HUMIDITY_OFFSET_STR, calibrate_humd_offset_menu_callback, 0, true, 0};
    calibrate_menu_items[3] = {"PID", calibrate_pid_menu_callback, 0, false, 0};
    calibrate_menu_items[4] = {MOTOR_ROTATION_STR,
                               calibrate_motor_menu_callback,
                               (float)eeprom_read_egg_rotation_duration(),
                               true,
                               0};

    calibrate_menu = new Menu(calibrate_menu_items, settings_menu, 5);
}

void calibrate_temp_offset_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = calibrate_temp_offset_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    changing_value(item, -20, 20, thermostat->get_temp_correction());
    thermostat->set_temp_correction(item->value);
}
void calibrate_humd_offset_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        // selected_callback = calibrate_humd_offset_menu_callback;
        // TODO: When humidifier is implemented, uncomment the line above
        selected_callback = NULL;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    /* changing_value(item, -20, 20, humdifier->get_humd_correction()); */
    /* humdifier->set_humd_correction(item->value); */
}
void calibrate_pid_menu_callback() { curr_menu = pid_menu; }
void calibrate_motor_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = calibrate_motor_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    changing_value(item, 0, 60, eeprom_read_egg_rotation_duration());
    eeprom_write_egg_rotation_duration(item->value);
}

// --------------------------------| PID Menu |---------------------------------

void EggCubatorUI::create_pid_menu() {
    pid_terms_t pid_terms;
    eeprom_read_temp_pid(&pid_terms);
    pid_menu_items[0] = {GO_BACK_STR, NULL, 0};
    pid_menu_items[1] = {"kp", pid_p_menu_callback, pid_terms.kp, true, 0};
    pid_menu_items[2] = {"ki", pid_i_menu_callback, pid_terms.ki, true, 0};
    pid_menu_items[3] = {"kd", pid_d_menu_callback, pid_terms.kd, true, 0};

    pid_menu = new Menu(pid_menu_items, calibrate_menu, 4);
}

void pid_p_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = pid_p_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    pid_terms_t pid_terms;
    eeprom_read_temp_pid(&pid_terms);

    changing_value(item, 0, 100, pid_terms.kp);

    pid_terms.kp = item->value;
    eeprom_write_temp_pid(pid_terms);
}
void pid_i_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = pid_i_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    pid_terms_t pid_terms;
    eeprom_read_temp_pid(&pid_terms);

    changing_value(item, 0, 100, pid_terms.ki);

    pid_terms.ki = item->value;
    eeprom_write_temp_pid(pid_terms);
}
void pid_d_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = pid_d_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }
    pid_terms_t pid_terms;
    eeprom_read_temp_pid(&pid_terms);

    changing_value(item, 0, 100, pid_terms.kd);

    pid_terms.kd = item->value;
    eeprom_write_temp_pid(pid_terms);
}

// ----------------------------| Eggs Settings Menu |---------------------------

void EggCubatorUI::create_eggs_settings_menu() {
    eggs_settings_menu_items[0] = {GO_BACK_STR, NULL, 0};
    eggs_settings_menu_items[1] = {
        CHICKEN_STR, settings_chicken_menu_callback, 0, false, 0};
    eggs_settings_menu_items[2] = {
        QUAIL_STR, settings_quail_menu_callback, 0, false, 0};
    eggs_settings_menu_items[3] = {DUCK_STR, settings_duck_menu_callback, 0, false, 0};
    eggs_settings_menu_items[4] = {
        TURKEY_STR, settings_turkey_menu_callback, 0, false, 0};
    eggs_settings_menu_items[5] = {
        GOOSE_STR, settings_goose_menu_callback, 0, false, 0};
    eggs_settings_menu_items[6] = {
        PIGEON_STR, settings_pigeon_menu_callback, 0, false, 0};

    eggs_settings_menu = new Menu(eggs_settings_menu_items, settings_menu, 7);
}

void settings_chicken_menu_callback() {}
void settings_quail_menu_callback() {}
void settings_duck_menu_callback() {}
void settings_turkey_menu_callback() {}
void settings_goose_menu_callback() {}
void settings_pigeon_menu_callback() {}

// -----------------------------| Egg Config Menu |-----------------------------

void EggCubatorUI::create_chicken_egg_config_menu() {
    // TODO: Missing callbacks declarations
    chicken_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    chicken_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    chicken_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    chicken_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    chicken_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    chicken_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    chicken_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(chicken_egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::create_quail_egg_config_menu() {
    // TODO: Missing callbacks declarations
    quail_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    quail_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    quail_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    quail_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    quail_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    quail_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    quail_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(quail_egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::create_duck_egg_config_menu() {
    // TODO: Missing callbacks declarations
    duck_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    duck_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    duck_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    duck_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    duck_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    duck_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    duck_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(duck_egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::create_goose_egg_config_menu() {
    // TODO: Missing callbacks declarations
    goose_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    goose_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    goose_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    goose_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    goose_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    goose_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    goose_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(goose_egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::create_turkey_egg_config_menu() {
    // TODO: Missing callbacks declarations
    turkey_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    turkey_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    turkey_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    turkey_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    turkey_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    turkey_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    turkey_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(turkey_egg_config_menu_items, eggs_settings_menu, 7);
}

void EggCubatorUI::create_pigeon_egg_config_menu() {
    // TODO: Missing callbacks declarations
    pigeon_egg_config_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    pigeon_egg_config_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    pigeon_egg_config_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    pigeon_egg_config_menu_items[3] = {PERIOD_STR, NULL, 0, true, 0};
    pigeon_egg_config_menu_items[4] = {
        ROTATION_PERIOD_STR, tune_rot_period_menu_callback, 0, true, 0};
    pigeon_egg_config_menu_items[5] = {START_OF_ROTATION_STR, NULL, 0, true, 0};
    pigeon_egg_config_menu_items[6] = {STOP_INCUBATION_STR, NULL, 0, true, 0};

    egg_config_menu = new Menu(pigeon_egg_config_menu_items, eggs_settings_menu, 7);
}

// TODO: we need to check the current egg selected
void config_chicken_menu_callback() {}
void config_quail_menu_callback() {}
void config_goose_menu_callback() {}
void config_duck_menu_callback() {}
void config_turkey_menu_callback() {}
void config_pigeon_menu_callback() {}

// ----------------------------| In Incubation Menu |---------------------------

void EggCubatorUI::create_incubation_main_menu() {
    incubation_main_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    incubation_main_menu_items[1] = {TUNE_STR, tune_menu_callback, 0, false, 0};
    incubation_main_menu_items[2] = {
        STOP_INCUBATION_STR, stop_incubation_menu_callback, 0, false, 0};

    incubation_main_menu = new Menu(incubation_main_menu_items, NULL, 3);
}

void tune_menu_callback() { curr_menu = tune_menu; }
void stop_incubation_menu_callback() {
    routine->stop_incubation();
    curr_menu = NULL;
}

// --------------------------------| Tune Menu |--------------------------------

void EggCubatorUI::create_tune_menu() {
    tune_menu_items[0] = {GO_BACK_STR, NULL, 0, false, 0};
    tune_menu_items[1] = {
        TARGET_TEMPERATURE_STR, tune_target_temp_menu_callback, temp_target, true, 0};
    tune_menu_items[2] = {
        TARGET_HUMIDITY_STR, tune_target_humd_menu_callback, humd_target, true, 0};
    tune_menu_items[3] = {ROTATION_PERIOD_STR,
                          tune_rot_period_menu_callback,
                          (float)eeprom_read_egg_rotation_duration(),
                          true,
                          0};

    tune_menu = new Menu(tune_menu_items, incubation_main_menu, 4);
}

void tune_target_temp_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = tune_target_temp_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    changing_value(item, 0, 50, temp_target);
    temp_target = item->value;
}

void tune_target_humd_menu_callback() {
    menu_item_t *item = curr_menu->selected_item_ptr();
    if (selected_callback == NULL) {
        selected_callback = tune_target_humd_menu_callback;
        item->precision = 1;
        prev_encoder_pos = encoder->getPosition();
        step = 1.0;
    }

    changing_value(item, 10, 100, humd_target);
    humd_target = item->value;
}

// TODO: missing callback declaration
void tune_rot_period_menu_callback() {}

void EggCubatorUI::create_menus() {
    create_main_menu();
    create_pid_menu();
    create_incubate_menu();
    create_settings_menu();
    /* create_egg_config_menu(); */
    create_preheat_menu();
    create_incubation_main_menu();
    /* create_eggs_settings_menu(); */
    create_calibrate_menu();
    create_tune_menu();
}

void EggCubatorUI::update_menu_items_values() {}
