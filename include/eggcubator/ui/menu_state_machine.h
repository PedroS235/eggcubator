#ifndef MENU_STATE_MACHINE_H
#define MENU_STATE_MACHINE_H

#include <Arduino.h>

#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"
#include "eggcubator/egg_factory.h"
#include "eggcubator/incubation.h"
#include "eggcubator/ui/menu.h"

// UI States
typedef enum {
    MAIN_SCREEN,
    INCUBATION_SCREEN,
    MAIN_MENU,
    INCUBATION_MENU,
    PREHEAT_MENU,
    SETTINGS_MENU,
    HEATER_MENU,
    HUMIDIFIER_MENU,
    IN_INCUBATION_MENU,
    IN_INCUBATION_TUNE_MENU,
    CHANGING_VALUE
} menu_state_e;

typedef enum { MOVE_UP, CLICK, MOVE_DOWN } menu_event_e;

const char *state_to_string(menu_state_e state);

void log_state_transition(menu_state_e from, menu_state_e to);
void log_event(menu_event_e event);

const char *event_to_string(menu_event_e event);

class MenuStateMachine {
   private:
    menu_state_e _state_before_changing_value;
    menu_state_e _curr_state;
    ValueMenuItem *_changing_value_item;
    Menu *_curr_menu;
    float chaging_value_precision = 1.0;
    IncubationRoutine *_incubation;
    Heater *_heater;
    Humidifier *_humidifier;

   public:
    MenuStateMachine(IncubationRoutine *incubation,
                     Heater *heater,
                     Humidifier *humidifier);
    Menu *get_curr_menu();
    void set_curr_menu(Menu *new_menu);
    void handle_event(menu_event_e event);
    void handle_main_screen_event(menu_event_e event);
    void handle_incubation_screen_event(menu_event_e event);
    void handle_main_menu_event(menu_event_e event);
    void handle_incubation_menu_event(menu_event_e event);
    void handle_preheat_menu_event(menu_event_e event);
    void handle_settings_menu_event(menu_event_e event);
    void handle_heater_menu_event(menu_event_e event);
    void handle_humidifier_menu_event(menu_event_e event);
    void handle_in_incubation_menu_event(menu_event_e event);
    void handle_in_incubation_tune_menu_event(menu_event_e event);
    void handle_changing_value_event(menu_event_e event);
    void apply_value_changed(ValueMenuItem *item);
};

#endif  // !MENU_STATE_MACHINE_H
