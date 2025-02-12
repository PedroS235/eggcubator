#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

#include "eggcubator/extras/filters.h"

class Thermistor {
   public:
    Thermistor(uint8_t pin, uint32_t pullup_res);
    esp_err_t read(float* output);

   private:
    float _resistance_to_temperature(float resistance);
    float _adc_to_resistance();

   private:
    uint8_t _pin;
    uint32_t _series_res;
    MovingAvgFilter* _temp_filter;
    EMAFilter* _adc_filter;
    int _raw_reading;
};

#endif  // !THERMISTOR_H
