#include "eggcubator/ui/menu.h"

#include "eggcubator/egg_factory.h"
#include "eggcubator/ui/menu_factory.h"

const char *state_to_string(menu_state_e state) {
    switch (state) {
        case MAIN_SCREEN:
            return "MAIN_SCREEN";
        case INCUBATION_SCREEN:
            return "INCUBATION_SCREEN";
        case MAIN_MENU:
            return "MAIN_MENU";
        case INCUBATION_MENU:
            return "INCUBATION_MENU";
        case PREHEAT_MENU:
            return "PREHEAT_MENU";
        case SETTINGS_MENU:
            return "SETTINGS_MENU";
        case HEATER_MENU:
            return "HEATER_MENU";
        case HUMIDIFIER_MENU:
            return "HUMIDIFIER_MENU";
        case IN_INCUBATION_MENU:
            return "IN_INCUBATION_MENU";
        case IN_INCUBATION_TUNE_MENU:
            return "IN_INCUBATION_TUNE_MENU";
        case CHANGING_VALUE:
            return "CHANGING_VALUE";
        default:
            return "UNKNOWN_STATE";
    }
}

void log_state_transition(menu_state_e from, menu_state_e to) {
    log_d("MenuStateMachine[NEW_STATE]:  %s --> %s",
          state_to_string(from),
          state_to_string(to));
}

const char *event_to_string(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            return "MOVE_UP";
        case CLICK:
            return "CLICK";
        case MOVE_DOWN:
            return "MOVE_DOWN";
        default:
            return "UNKNOWN_EVENT";
    }
}

void log_event(menu_event_e event) {
    log_d("MenuStateMachine[EVENT]: %s", event_to_string(event));
}

MenuStateMachine::MenuStateMachine(IncubationRoutine *incubation)
    : _incubation(incubation) {
    _curr_menu = nullptr;
    _curr_state = MAIN_SCREEN;
}

Menu *MenuStateMachine::get_curr_menu() { return _curr_menu; }

void MenuStateMachine::handle_event(menu_event_e event) {
    // log_event(event);
    switch (_curr_state) {
        case MAIN_SCREEN:
            handle_main_screen_event(event);
            break;
        case INCUBATION_SCREEN:
            handle_incubation_screen_event(event);
            break;
        case MAIN_MENU:
            handle_main_menu_event(event);
            break;
        case INCUBATION_MENU:
            handle_incubation_menu_event(event);
            break;
        case PREHEAT_MENU:
            handle_preheat_menu_event(event);
            break;
        case SETTINGS_MENU:
            handle_settings_menu_event(event);
            break;
        case HEATER_MENU:
            handle_heater_menu_event(event);
        case HUMIDIFIER_MENU:
            handle_humidifier_menu_event(event);
            break;
        case IN_INCUBATION_MENU:
            handle_in_incubation_menu_event(event);
            break;
        case IN_INCUBATION_TUNE_MENU:
            handle_in_incubation_tune_menu_event(event);
            break;
        case CHANGING_VALUE:
            handle_changing_value_event(event);
            break;
    }
}

void MenuStateMachine::handle_main_screen_event(menu_event_e event) {
    switch (event) {
        case CLICK:
            log_state_transition(MAIN_SCREEN, MAIN_MENU);
            _curr_state = MAIN_MENU;
            _curr_menu = MenuFactory::createMainMenu();
            break;
        default:
            log_w("MAIN_SCREEN does not have an event %s. Only CLICK is valid.",
                  event_to_string(event));
            break;
    }
}
void MenuStateMachine::handle_incubation_screen_event(menu_event_e event) {
    switch (event) {
        case CLICK:
            log_state_transition(INCUBATION_SCREEN, IN_INCUBATION_MENU);
            _curr_state = IN_INCUBATION_MENU;
            _curr_menu = MenuFactory::createInIncubationMenu();
            break;
        default:
            log_w("MAIN_SCREEN does not have an event %s. Only CLICK is valid.",
                  event_to_string(event));
            break;
    }
}

void MenuStateMachine::handle_main_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(MAIN_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete _curr_menu;
                    _curr_menu = nullptr;
                    break;
                case 1:
                    log_state_transition(MAIN_MENU, INCUBATION_MENU);
                    _curr_state = INCUBATION_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createIncubationMenu();
                    break;
                case 2:
                    log_state_transition(MAIN_MENU, PREHEAT_MENU);
                    _curr_state = PREHEAT_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createPreheatMenu();
                    break;
                case 3:
                    log_state_transition(MAIN_MENU, SETTINGS_MENU);
                    _curr_state = SETTINGS_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createSettingsMenu();
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}
void MenuStateMachine::handle_incubation_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(INCUBATION_MENU, MAIN_MENU);
                    _curr_state = MAIN_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createMainMenu();
                    break;
                    // TODO: Start incubation
                case 1:  // Chicken
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;

                    _incubation->start_incubation(EggFactory::createChickenEgg());
                    break;
                case 2:  // Quail
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;

                    _incubation->start_incubation(EggFactory::createQuailEgg());
                    break;
                case 3:  // Duck
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;

                    _incubation->start_incubation(EggFactory::createDuckEgg());
                    break;
                case 4:  // Turkey
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);

                    _incubation->start_incubation(EggFactory::createTurkeyEgg());
                    _curr_menu = nullptr;
                    break;
                case 5:  // Goose
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;

                    _incubation->start_incubation(EggFactory::createGooseEgg());
                    break;
                case 6:  // Pigeon
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;

                    _incubation->start_incubation(EggFactory::createPigeonEgg());
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}
void MenuStateMachine::handle_preheat_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(PREHEAT_MENU, MAIN_MENU);
                    _curr_state = MAIN_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createMainMenu();
                    break;
                case 1:  // Manual Temperature
                    log_state_transition(PREHEAT_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = PREHEAT_MENU;
                    // TODO: curr menu
                    break;
                    // TODO: Update Heater Target Temperature
                case 2:  // Chicken
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 3:  // Quail
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 4:  // Duck
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 5:  // Turkey
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 6:  // Goose
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 7:  // Pigeon
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}
void MenuStateMachine::handle_settings_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(SETTINGS_MENU, MAIN_MENU);
                    _curr_state = MAIN_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createMainMenu();
                    break;
                case 1:
                    log_state_transition(SETTINGS_MENU, HEATER_MENU);
                    _curr_state = HEATER_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createHeaterMenu();
                    break;
                case 2:
                    log_state_transition(SETTINGS_MENU, HUMIDIFIER_MENU);
                    _curr_state = HUMIDIFIER_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createHumidifierMenu();
                    break;
                case 3:
                    log_state_transition(SETTINGS_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = SETTINGS_MENU;
                    break;
                case 4:  // Save Settings into eeprom
                    break;
                case 6:  // Reset Settings to defaults
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}
void MenuStateMachine::handle_heater_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(HEATER_MENU, SETTINGS_MENU);
                    _curr_state = SETTINGS_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createSettingsMenu();
                    break;
                case 1:  // kp
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 2:  // ki
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 3:  // kd
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 4:  // Temp offset
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HEATER_MENU;
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}
void MenuStateMachine::handle_humidifier_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(HUMIDIFIER_MENU, SETTINGS_MENU);
                    _curr_state = SETTINGS_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createSettingsMenu();
                    break;
                case 1:  // kp
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 2:  // ki
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 3:  // kd
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 4:  // Temp offset
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}

void MenuStateMachine::handle_in_incubation_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(IN_INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    break;
                case 1:  // Tune
                    log_state_transition(IN_INCUBATION_MENU, IN_INCUBATION_TUNE_MENU);
                    _curr_state = IN_INCUBATION_TUNE_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createInIncubationTuneMenu();
                    break;
                case 2:  // Stop Incubation
                    log_state_transition(IN_INCUBATION_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    delete (_curr_menu);
                    _curr_menu = nullptr;
                    _incubation->stop_incubation();
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}

void MenuStateMachine::handle_in_incubation_tune_menu_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            _curr_menu->move_up();
            break;
        case CLICK:
            switch (_curr_menu->get_idx()) {
                case 0:  // Go Back
                    log_state_transition(IN_INCUBATION_TUNE_MENU, IN_INCUBATION_MENU);
                    _curr_state = IN_INCUBATION_MENU;
                    delete (_curr_menu);
                    _curr_menu = MenuFactory::createIncubationMenu();
                    break;
                case 1:  // Target Temperature
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = IN_INCUBATION_TUNE_MENU;
                    break;
                case 2:  // Target Humidity
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = IN_INCUBATION_TUNE_MENU;
                    break;
                case 3:  // Motor Rotation
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _state_before_changing_value = IN_INCUBATION_TUNE_MENU;
                    break;
            }
            break;
        case MOVE_DOWN:
            _curr_menu->move_down();
            break;
    }
}

void MenuStateMachine::handle_changing_value_event(menu_event_e event) {
    switch (event) {
        case MOVE_UP:
            break;
        case CLICK:
            _curr_state = _state_before_changing_value;
            break;
        case MOVE_DOWN:
            break;
    }
}
