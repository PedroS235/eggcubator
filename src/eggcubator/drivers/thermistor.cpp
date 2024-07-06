#include "eggcubator/drivers/thermistor.h"

#include "esp32-hal-adc.h"
#include "esp32-hal-log.h"

static const float ADC_RESOLUTION = 12;
static const float MAX_ADC_VALUE = 4095;  // 2^12
static const float KELVIN_IN_CELSIUS = 273.15;
static const float STEINHART_COEFF_A = 0.001129148;
static const float STEINHART_COEFF_B =
    0.000234125;  // Note the correction in the coefficient
static const float STEINHART_COEFF_C = 0.0000000876741;

Thermistor::Thermistor(uint8_t pin, uint32_t pullup_res) {
    _pin = pin;
    _pullup_res = pullup_res;
    pinMode(_pin, ANALOG);
    analogReadResolution(ADC_RESOLUTION);
}

float Thermistor::read() {
    int reading = analogRead(_pin);

    // Prevent division by zero error
    if (reading == 0) {
        log_e("Thermistor reading is not correct. Is thermistor connected?");
        return -KELVIN_IN_CELSIUS;
    }

    // Calculate the resistance of the thermistor
    float resistance = _pullup_res * ((MAX_ADC_VALUE / (float)reading) - 1.0);
    float resistance_ln = log(resistance);

    // Steinhart-Hart equation
    float tempK =
        1.0 / (STEINHART_COEFF_A + STEINHART_COEFF_B * resistance_ln +
               STEINHART_COEFF_C * resistance_ln * resistance_ln * resistance_ln);

    float tempC = tempK - KELVIN_IN_CELSIUS;

    return tempC;
}
