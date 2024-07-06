#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

class Thermistor {
   public:
    Thermistor(uint8_t pin, uint32_t pullup_res);
    float read();

   private:
    float _resistance_to_temperature(float resistance);
    float _adc_to_resistance();

   private:
    uint8_t _pin;
    uint32_t _pullup_res;
};

#endif  // !THERMISTOR_H
