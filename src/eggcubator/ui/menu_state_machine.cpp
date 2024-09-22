#include "eggcubator/ui/menu_state_machine.h"

#include "eggcubator/core/humidifier.h"
#include "eggcubator/egg_factory.h"
#include "eggcubator/ui/menu.h"
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

MenuStateMachine::MenuStateMachine(IncubationRoutine *incubation,
                                   Heater *heater,
                                   Humidifier *humidifier)
    : _incubation(incubation), _heater(heater), _humidifier(humidifier) {
    _curr_menu = nullptr;
    _curr_state = MAIN_SCREEN;
}

Menu *MenuStateMachine::get_curr_menu() { return _curr_menu; }

void MenuStateMachine::set_curr_menu(Menu *new_menu) {
    if (_curr_menu != nullptr) {
        delete _curr_menu;
        _curr_menu = nullptr;
    }
    _curr_menu = new_menu;
}

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
            break;
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
            set_curr_menu(MenuFactory::createMainMenu());
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
            set_curr_menu(MenuFactory::createInIncubationMenu());
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
                    set_curr_menu(nullptr);
                    break;
                case 1:
                    log_state_transition(MAIN_MENU, INCUBATION_MENU);
                    _curr_state = INCUBATION_MENU;
                    set_curr_menu(MenuFactory::createIncubationMenu());
                    break;
                case 2:
                    log_state_transition(MAIN_MENU, PREHEAT_MENU);
                    _curr_state = PREHEAT_MENU;
                    set_curr_menu(
                        MenuFactory::createPreheatMenu(_heater->get_target()));
                    break;
                case 3:
                    log_state_transition(MAIN_MENU, SETTINGS_MENU);
                    _curr_state = SETTINGS_MENU;
                    set_curr_menu(MenuFactory::createSettingsMenu(
                        _incubation->get_motor_rotation()));
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
        case CLICK: {
            int idx = _curr_menu->get_idx();
            switch (idx) {
                case 0:  // Go Back
                    log_state_transition(INCUBATION_MENU, MAIN_MENU);
                    _curr_state = MAIN_MENU;
                    set_curr_menu(MenuFactory::createMainMenu());
                    break;
                default:
                    log_state_transition(INCUBATION_MENU, INCUBATION_SCREEN);
                    _curr_state = INCUBATION_SCREEN;
                    set_curr_menu(nullptr);
                    _incubation->start_incubation(
                        EggFactory::createEggFromIdx(idx - 1));
                    break;
            }
            break;
        }
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
        case CLICK: {
            int idx = _curr_menu->get_idx();
            switch (idx) {
                case 0:  // Go Back
                    log_state_transition(PREHEAT_MENU, MAIN_MENU);
                    _curr_state = MAIN_MENU;
                    set_curr_menu(MenuFactory::createMainMenu());
                    break;
                case 1: {  // Manual Temperature
                    log_state_transition(PREHEAT_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = PREHEAT_MENU;
                    break;
                }
                default:
                    log_state_transition(PREHEAT_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    set_curr_menu(nullptr);
                    _heater->set_temp_target(
                        EggFactory::createEggFromIdx(idx).target_temp);
                    break;
            }
            break;
        }
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
                    set_curr_menu(MenuFactory::createMainMenu());
                    break;
                case 1:
                    log_state_transition(SETTINGS_MENU, HEATER_MENU);
                    _curr_state = HEATER_MENU;
                    set_curr_menu(MenuFactory::createHeaterMenu(
                        _heater->get_pid_terms(), _heater->get_temp_correction()));
                    break;
                case 2:
                    log_state_transition(SETTINGS_MENU, HUMIDIFIER_MENU);
                    _curr_state = HUMIDIFIER_MENU;
                    set_curr_menu(MenuFactory::createHumidifierMenu(
                        _humidifier->get_pid_terms(),
                        _humidifier->get_humidity_correction()));
                    break;
                case 3:
                    log_state_transition(SETTINGS_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
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
                    set_curr_menu(MenuFactory::createSettingsMenu(
                        _incubation->get_motor_rotation()));
                    break;
                case 1:  // kp
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 2:  // ki
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 3:  // kd
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HEATER_MENU;
                    break;
                case 4:  // Temp offset
                    log_state_transition(HEATER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
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
                    set_curr_menu(MenuFactory::createSettingsMenu(
                        _incubation->get_motor_rotation()));
                    break;
                case 1:  // kp
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 2:  // ki
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 3:  // kd
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = HUMIDIFIER_MENU;
                    break;
                case 4:  // Temp offset
                    log_state_transition(HUMIDIFIER_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
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
                    set_curr_menu(nullptr);
                    break;
                case 1:  // Tune
                    log_state_transition(IN_INCUBATION_MENU, IN_INCUBATION_TUNE_MENU);
                    _curr_state = IN_INCUBATION_TUNE_MENU;
                    set_curr_menu(MenuFactory::createInIncubationTuneMenu(
                        _heater->get_target(),
                        _humidifier->get_target(),
                        _incubation->get_motor_rotation()));
                    break;
                case 2:  // Stop Incubation
                    log_state_transition(IN_INCUBATION_MENU, MAIN_SCREEN);
                    _curr_state = MAIN_SCREEN;
                    set_curr_menu(nullptr);
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
                    set_curr_menu(MenuFactory::createInIncubationMenu());
                    break;
                case 1:  // Target Temperature
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = IN_INCUBATION_TUNE_MENU;
                    break;
                case 2:  // Target Humidity
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
                    _state_before_changing_value = IN_INCUBATION_TUNE_MENU;
                    break;
                case 3:  // Motor Rotation
                    log_state_transition(IN_INCUBATION_TUNE_MENU, CHANGING_VALUE);
                    _curr_state = CHANGING_VALUE;
                    _changing_value_item = _curr_menu->get_selected_value_item();
                    _changing_value_item->increment_precision();
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
    if (_changing_value_item == nullptr) return;
    switch (event) {
        case MOVE_DOWN:
            switch (_changing_value_item->get_precision()) {
                case 1:
                    _changing_value_item->set_value(_changing_value_item->get_value() +
                                                    1.0);
                    break;
                case 2:
                    _changing_value_item->set_value(_changing_value_item->get_value() +
                                                    0.1);
                    break;
            }

            break;
        case CLICK: {
            int new_precision = _changing_value_item->increment_precision();

            if (new_precision == 0) {
                log_state_transition(CHANGING_VALUE, _state_before_changing_value);
                _curr_state = _state_before_changing_value;
                apply_value_changed(_changing_value_item);
                _changing_value_item = nullptr;
            }
        }

        break;
        case MOVE_UP:
            switch (_changing_value_item->get_precision()) {
                case 1:
                    _changing_value_item->set_value(_changing_value_item->get_value() -
                                                    1.0);
                    break;
                case 2:
                    _changing_value_item->set_value(_changing_value_item->get_value() -
                                                    0.1);
                    break;
            }
            break;
    }
}

void MenuStateMachine::apply_value_changed(ValueMenuItem *item) {
    if (strcmp(item->get_text(), MANUAL_STR) == 0 && _curr_state == PREHEAT_MENU) {
        _heater->set_temp_target(item->get_value());
    } else if (strcmp(item->get_text(), "kp") == 0 && _curr_state == HEATER_MENU) {
        _heater->update_pid_kp(item->get_value());
    } else if (strcmp(item->get_text(), "ki") == 0 && _curr_state == HEATER_MENU) {
        _heater->update_pid_ki(item->get_value());
    } else if (strcmp(item->get_text(), "kd") == 0 && _curr_state == HEATER_MENU) {
        _heater->update_pid_kd(item->get_value());
    } else if (strcmp(item->get_text(), TEMPERATURE_OFFSET_STR) == 0) {
        _heater->set_temp_correction(item->get_value());
    } else if (strcmp(item->get_text(), "kp") == 0 && _curr_state == HUMIDIFIER_MENU) {
        _humidifier->update_pid_kp(item->get_value());
    } else if (strcmp(item->get_text(), "ki") == 0 && _curr_state == HUMIDIFIER_MENU) {
        _humidifier->update_pid_ki(item->get_value());
    } else if (strcmp(item->get_text(), "kd") == 0 && _curr_state == HUMIDIFIER_MENU) {
        _humidifier->update_pid_kd(item->get_value());
    } else if (strcmp(item->get_text(), HUMIDITY_OFFSET_STR) == 0) {
        _humidifier->set_humidity_correction(item->get_value());
    } else if (strcmp(item->get_text(), MOTOR_ROTATION_STR) == 0) {
        _incubation->set_motor_rotation(item->get_value());
    } else if (strcmp(item->get_text(), TARGET_TEMPERATURE_STR) == 0) {
        _heater->set_temp_target(item->get_value());
    } else if (strcmp(item->get_text(), TARGET_HUMIDITY_STR) == 0) {
        _humidifier->set_humidity_target(item->get_value());
    }
}
