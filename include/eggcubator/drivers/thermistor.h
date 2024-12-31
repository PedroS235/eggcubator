#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

#include "eggcubator/extras/ema_filter.h"
#include "eggcubator/extras/holt_winters_filter.h"
#include "eggcubator/extras/moving_avg_filter.h"

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
    HoltWintersFilter* _filter;
};

#endif  // !THERMISTOR_H
