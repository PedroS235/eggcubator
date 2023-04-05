#include "eggcubator/timer.h"

using namespace eggcubator;

Timer::Timer() {
    time_interval = 1000;
    elapsed_time = millis();
    time = {0, 0, 0, 0};
}

uint8_t Timer::get_day() { return time.day; }

uint8_t Timer::get_hour() { return time.hour; }

uint8_t Timer::get_minute() { return time.minute; }

uint8_t Timer::get_seconds() { return time.second; }

void Timer::print_time() {
    if (time.day > 0) {
        Serial.print(time.day);
        Serial.println(" days");
    } else {
        Serial.print(time.hour);
        Serial.print(":");
        Serial.print(time.minute);
        Serial.print(":");
        Serial.println(time.second);
    }
}

void Timer::start() {
    elapsed_time = millis();
    is_running = true;
    time = {0, 0, 0, 0};
}

void Timer::update() {
    if (is_running) {
        unsigned long now = millis();
        if (now - elapsed_time > time_interval) {
            elapsed_time = now;
            time.second++;
        }

        if (time.second == 60) {
            time.minute++;
            time.second = 0;
        }

        if (time.minute == 60) {
            time.hour++;
            time.minute = 0;
        }

        if (time.hour == 24) {
            time.day++;
            time.hour = 0;
        }
    }
}
