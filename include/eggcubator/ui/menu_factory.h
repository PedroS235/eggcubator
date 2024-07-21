#ifndef FACTORY_H
#define FACTORY_H

#include "eggcubator/ui/language/language.h"

typedef struct {
    const char* text;
    bool has_value;
    double value;
    int precision;
} menu_item_t;

class Menu {
   private:
    menu_item_t* _items;
    int _size;
    int _idx;

   public:
    Menu(menu_item_t* items, int size) {
        _items = items;
        _size = size;
        _idx = 0;
    }
    void move_up() {
        if (_idx > 0) {
            _idx--;
        }
    }
    void move_down() {
        if (_idx < _size - 1) {
            _idx++;
        }
    }
    int get_idx() { return _idx; }
    int get_size() { return _size; }
    menu_item_t* get_items() { return _items; }
    menu_item_t* get_selected_item() { return &_items[_idx]; }
};

class MenuFactory {
   public:
    static Menu* createMainMenu() {
        static menu_item_t mainMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = INCUBATE_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = PREHEAT_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = SETTINGS_STR, .has_value = false, .value = 0, .precision = 0},
        };
        return new Menu(mainMenuItems, 4);
    }
    static Menu* createIncubationMenu() {
        static menu_item_t incubationMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = CHICKEN_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = QUAIL_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = DUCK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = TURKEY_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = GOOSE_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = PIGEON_STR, .has_value = false, .value = 0, .precision = 0},
        };
        return new Menu(incubationMenuItems, 7);
    }

    static Menu* createPreheatMenu() {
        static menu_item_t preheatMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = MANUAL_STR, .has_value = true, .value = 0.0, .precision = 0},
            {.text = CHICKEN_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = QUAIL_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = DUCK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = TURKEY_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = GOOSE_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = PIGEON_STR, .has_value = false, .value = 0, .precision = 0},
        };
        return new Menu(preheatMenuItems, 8);
    }

    static Menu* createSettingsMenu() {
        static menu_item_t settingsMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = HEATER_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = HUMIDIFIER_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = MOTOR_ROTATION_STR,
             .has_value = true,
             .value = 0.0,
             .precision = 0},
            {.text = SAVE_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = RESET_STR, .has_value = false, .value = 0, .precision = 0},
        };
        return new Menu(settingsMenuItems, 6);
    }

    static Menu* createHeaterMenu() {
        static menu_item_t heaterMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = "kp", .has_value = true, .value = 0, .precision = 0},
            {.text = "ki", .has_value = true, .value = 0, .precision = 0},
            {.text = "kd", .has_value = true, .value = 0.0, .precision = 0},
            {.text = TEMPERATURE_OFFSET_STR,
             .has_value = true,
             .value = 0,
             .precision = 0},
        };
        return new Menu(heaterMenuItems, 5);
    }

    static Menu* createHumidifierMenu() {
        static menu_item_t HumidifierMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = "kp", .has_value = true, .value = 0, .precision = 0},
            {.text = "ki", .has_value = true, .value = 0, .precision = 0},
            {.text = "kd", .has_value = true, .value = 0.0, .precision = 0},
            {.text = HUMIDITY_OFFSET_STR,
             .has_value = true,
             .value = 0,
             .precision = 0},
        };
        return new Menu(HumidifierMenuItems, 5);
    }

    static Menu* createInIncubationMenu() {
        static menu_item_t InIncubationMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = TUNE_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = STOP_INCUBATION_STR,
             .has_value = false,
             .value = 0,
             .precision = 0},
        };
        return new Menu(InIncubationMenuItems, 3);
    }

    static Menu* createInIncubationTuneMenu() {
        static menu_item_t InIncubationTuneMenuItems[] = {
            {.text = GO_BACK_STR, .has_value = false, .value = 0, .precision = 0},
            {.text = TARGET_TEMPERATURE_STR,
             .has_value = true,
             .value = 0,
             .precision = 0},
            {.text = TARGET_HUMIDITY_STR,
             .has_value = true,
             .value = 0,
             .precision = 0},
            {.text = MOTOR_ROTATION_STR, .has_value = true, .value = 0, .precision = 0},
        };
        return new Menu(InIncubationTuneMenuItems, 4);
    }
};

#endif  // !FACTORY_H
