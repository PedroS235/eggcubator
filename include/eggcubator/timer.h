#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

namespace eggcubator {
typedef struct {
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_t;

class Timer {
   private:
    time_t time;
    unsigned long elapsed_time;
    unsigned long time_interval;
    bool is_running = false;

   public:
    Timer();
    uint8_t get_day();
    uint8_t get_hour();
    uint8_t get_minute();
    uint8_t get_seconds();
    void print_time();
    void update();
    void start();
};
};      // namespace eggcubator

#endif  // !TIMER_H
