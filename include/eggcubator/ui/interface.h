#ifndef INTERACE_H
#define INTERACE_H

#include "RotaryEncoder.h"
#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"
#include "eggcubator/extras/speaker.h"
#include "eggcubator/incubation.h"
#include "eggcubator/ui/display_manager.h"
#include "eggcubator/ui/menu.h"

class Interface {
   private:
    Heater* _heater;
    Humidifier* _humidifier;
    IncubationRoutine* _incubation;
    RotaryEncoder _encoder;
    Speaker _speaker;
    DisplayManager _display;
    MenuStateMachine _menuStateMachine;
    static Interface* _instance;  // Static instance pointer
    bool _button_has_been_pressed;

    void handle_encoder_events(menu_event_e event);
    void handle_encoder_button_event();

   public:
    Interface(Heater* heater, Humidifier* humidifier, IncubationRoutine* incubator);
    void init();

    static void move_down_callback();
    void encoder_callback();
    static void encoder_ISR();
    void move_down();
    static void move_up_callback();
    void move_up();
    // Hack to allow using the callbacks
    static void setInstance(Interface* inst) { _instance = inst; }

    void task(void* pvParameters);
};

#endif  // !INTERACE_H
