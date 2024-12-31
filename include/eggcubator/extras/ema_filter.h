#ifndef EMA_FILTER_H
#define EMA_FILTER_H

#include <Arduino.h>

class EMAFilter {
   private:
    float prev_reading = 0;
    float alpha = 0.3;

   public:
    EMAFilter(float alpha = 0.2) : alpha(alpha) {}

    float compute(float current_value) {
        float smooth_value = alpha * current_value + (1 - alpha) * prev_reading;
        prev_reading = current_value;
        return smooth_value;
    }
};

#endif  // !EMA_FILTER_H
