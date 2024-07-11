#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

class Speaker {
   public:
    Speaker(uint8_t pin);
    void startup_sound();
    void button_click_sound();
    void beep(unsigned int frequency, unsigned long duration);

   private:
    uint8_t _pin;
};

#endif  // !SPEAKER_H
