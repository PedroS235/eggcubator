#ifndef FACTORY_H
#define FACTORY_H

#include "eggcubator/ui/language/language.h"

typedef struct {
    const char* text;
} text_item_t;

typedef struct {
    const char* text;
    double value;
    int precision;
} value_item_t;

typedef struct {
    const char* text;
    bool checked;
} checkbox_item_t;

typedef enum { TEXT_ITEM, VALUE_ITEM, CHECKBOX_ITEM } menu_item_type_e;

typedef struct {
    menu_item_type_e type;
    union {
        text_item_t text_item;
        value_item_t value_item;
        checkbox_item_t checkbox_item;
    } item;
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
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {TEXT_ITEM, {.text_item = {INCUBATE_STR}}},
            {TEXT_ITEM, {.text_item = {PREHEAT_STR}}},
            {TEXT_ITEM, {.text_item = {SETTINGS_STR}}},
        };
        return new Menu(mainMenuItems, 4);
    }

    static Menu* createIncubationMenu() {
        static menu_item_t incubationMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {TEXT_ITEM, {.text_item = {CHICKEN_STR}}},
            {TEXT_ITEM, {.text_item = {QUAIL_STR}}},
            {TEXT_ITEM, {.text_item = {DUCK_STR}}},
            {TEXT_ITEM, {.text_item = {TURKEY_STR}}},
            {TEXT_ITEM, {.text_item = {GOOSE_STR}}},
            {TEXT_ITEM, {.text_item = {PIGEON_STR}}},
        };
        return new Menu(incubationMenuItems, 7);
    }

    static Menu* createPreheatMenu() {
        static menu_item_t preheatMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {VALUE_ITEM, {.value_item = {MANUAL_STR, 0.0, 0}}},
            {TEXT_ITEM, {.text_item = {CHICKEN_STR}}},
            {TEXT_ITEM, {.text_item = {QUAIL_STR}}},
            {TEXT_ITEM, {.text_item = {DUCK_STR}}},
            {TEXT_ITEM, {.text_item = {TURKEY_STR}}},
            {TEXT_ITEM, {.text_item = {GOOSE_STR}}},
            {TEXT_ITEM, {.text_item = {PIGEON_STR}}},
        };
        return new Menu(preheatMenuItems, 8);
    }

    static Menu* createSettingsMenu() {
        static menu_item_t settingsMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {TEXT_ITEM, {.text_item = {HEATER_STR}}},
            {TEXT_ITEM, {.text_item = {HUMIDIFIER_STR}}},
            {VALUE_ITEM, {.value_item = {MOTOR_ROTATION_STR, 0.0, 0}}},
            {TEXT_ITEM, {.text_item = {SAVE_STR}}},
            {TEXT_ITEM, {.text_item = {RESET_STR}}},
        };
        return new Menu(settingsMenuItems, 6);
    }

    static Menu* createHeaterMenu() {
        static menu_item_t heaterMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {VALUE_ITEM, {.value_item = {"kp", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {"ki", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {"kd", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {TEMPERATURE_OFFSET_STR, 0.0, 0}}},
        };
        return new Menu(heaterMenuItems, 5);
    }

    static Menu* createHumidifierMenu() {
        static menu_item_t humidifierMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {VALUE_ITEM, {.value_item = {"kp", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {"ki", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {"kd", 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {HUMIDITY_OFFSET_STR, 0.0, 0}}},
        };
        return new Menu(humidifierMenuItems, 5);
    }

    static Menu* createInIncubationMenu() {
        static menu_item_t inIncubationMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {TEXT_ITEM, {.text_item = {TUNE_STR}}},
            {TEXT_ITEM, {.text_item = {STOP_INCUBATION_STR}}},
        };
        return new Menu(inIncubationMenuItems, 3);
    }

    static Menu* createInIncubationTuneMenu() {
        static menu_item_t inIncubationTuneMenuItems[] = {
            {TEXT_ITEM, {.text_item = {GO_BACK_STR}}},
            {VALUE_ITEM, {.value_item = {TARGET_TEMPERATURE_STR, 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {TARGET_HUMIDITY_STR, 0.0, 0}}},
            {VALUE_ITEM, {.value_item = {MOTOR_ROTATION_STR, 0.0, 0}}},
        };
        return new Menu(inIncubationTuneMenuItems, 4);
    }
};

#endif  // !FACTORY_H
