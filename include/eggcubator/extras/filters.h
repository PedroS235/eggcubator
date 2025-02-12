#ifndef FILTERS_H
#define FILTERS_H

#include <Arduino.h>
#include <stdlib.h>

#define DEFAULT_WINDOW_SIZE 15

/**
 * @brief: Simple filter in order to smooth out sensor readings and reduce
 * the impact of sensor noises
 */
class MovingAvgFilter {
   private:
    float *_readings = NULL;
    uint8_t _curr_index = 0;
    int _window_size = DEFAULT_WINDOW_SIZE;

   public:
    /**
     * @brief Constructor of the class MovingAvgFilter
     *
     * @param window_size Size to be used for the average window
     * @param default_value Value to set the initial window
     */
    MovingAvgFilter(int window_size = DEFAULT_WINDOW_SIZE, float default_value = 22)
        : _window_size(window_size) {
        _readings = (float *)malloc(window_size * sizeof(float));
        for (int i = 0; i < window_size; i++) {
            _readings[i] = default_value;
        }
    }

    ~MovingAvgFilter() {
        if (_readings != NULL) {
            free(_readings);
        }
    }

    /**
     * @brief Computes the filtered value from the current measured value
     *
     * @param current_value is the current measured value of the sensor
     *
     * @return Filtered value
     */
    float compute(float current_value) {
        _readings[_curr_index] = current_value;
        _curr_index = (_curr_index + 1) % _window_size;

        float sum = 0;
        for (int i = 0; i < _window_size; i++) {
            sum += _readings[i];
        }

        return sum / _window_size;
    }
};

class EMAFilter {
   private:
    float _prev_reading = 0;
    float _alpha = 0.3;

   public:
    EMAFilter(float alpha = 0.2) : _alpha(alpha) {}

    float compute(float current_value) {
        float smooth_value = _alpha * current_value + (1 - _alpha) * _prev_reading;
        _prev_reading = current_value;
        return smooth_value;
    }
};

#endif  // !FILTERS_H
