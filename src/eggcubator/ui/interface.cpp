#include "eggcubator/ui/interface.h"

#include "eggcubator/core/humidifier.h"
#include "eggcubator/extras/speaker.h"
#include "eggcubator/ui/menu_state_machine.h"
#include "esp32-hal.h"

Interface* Interface::_instance = nullptr;

Interface::Interface(Heater* heater,
                     Humidifier* humidifier,
                     IncubationRoutine* incubator)
    : _heater(heater),
      _incubation(incubator),
      _humidifier(humidifier),
      _speaker(UI_SPEAKER_PIN),
      _encoder(UI_ENCODER_CLK_PIN, UI_ENCODER_DT_PIN, UI_ENCODER_SW_PIN),
      _menuStateMachine(incubator, heater, humidifier),
      _display() {
    _instance = this;
    _button_has_been_pressed = _encoder.is_button_pressed();
    attachInterrupt(digitalPinToInterrupt(UI_ENCODER_CLK_PIN), encoder_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(UI_ENCODER_DT_PIN), encoder_ISR, CHANGE);

    _encoder.attachTurnLeft(Interface::move_up_callback);
    _encoder.attachTurnRight(Interface::move_down_callback);
}

void Interface::init() {
    _display.draw_boot_screen("Eggcubator");
    _speaker.startup_sound();
    delay(UI_BOOTSCREEN_DURATION);
}

void Interface::encoder_ISR() {
    if (_instance != nullptr) _instance->encoder_callback();
}

void Interface::encoder_callback() { _encoder.tick(); }

void Interface::move_down_callback() {
    if (_instance != nullptr) _instance->handle_encoder_events(MOVE_DOWN);
}

void Interface::move_up_callback() {
    if (_instance != nullptr) _instance->handle_encoder_events(MOVE_UP);
}

void Interface::handle_encoder_events(menu_event_e event) {
    _menuStateMachine.handle_event(event);
}

void Interface::handle_encoder_button_event() {
    bool button_state = _encoder.is_button_pressed();
    if (button_state && !_button_has_been_pressed) {
        // _speaker.button_click_sound();
        handle_encoder_events(CLICK);
        _button_has_been_pressed = true;
    } else if (!button_state) {
        _button_has_been_pressed = false;
    }
}

void Interface::task(void* pvParameters) {
    for (;;) {
        log_v("Ticking Interface");

        handle_encoder_button_event();

        Menu* _curr_menu = _menuStateMachine.get_curr_menu();

        if (_curr_menu == nullptr) {
            if (_incubation->in_incubation()) {
                _display.draw_incubation_status_screen(
                    _heater->get_temp(),
                    _heater->get_target(),
                    _humidifier->get_humidity(),
                    _humidifier->get_target(),
                    _incubation->get_curr_time().get_time_t(),
                    29);
                continue;
            }
            _display.draw_status_screen(_heater->get_temp(),
                                        _heater->get_target(),
                                        _humidifier->get_humidity(),
                                        _humidifier->get_target());
            continue;
        }

        _display.draw_menu(_curr_menu);

        vTaskDelay(UI_REFRESH_RATE / portTICK_PERIOD_MS);
    }
}
