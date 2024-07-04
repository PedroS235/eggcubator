#include "eggcubator/core/humidifier.h"

#include "eggcubator/config/pins.h"

Humidifier::Humidifier(DHT *dht_sensor,
                       unsigned long humidity_reading_interval_,
                       float humidity_correction_)
    : humidity(NAN),
      humidity_target(0),
      prev_humidity_target(0),
      last_humidity_reading_time(0) {
    humidity_sensor = dht_sensor;
    pid = new PID(PID_SERVO_KP, PID_SERVO_KI, PID_SERVO_KD);

    humidity_reading_interval = humidity_reading_interval_;
    humidity_correction = humidity_correction_;
}

void Humidifier::update_humidity() {
    unsigned long now = millis();
    if (now - last_humidity_reading_time >= humidity_reading_interval) {
        const float reading = humidity_sensor->readHumidity();
        if (!isnan(reading)) {
            humidity = reading + humidity_correction;
        } else {
            humidity = NAN;
        }
        last_humidity_reading_time = now;
    }
}

float Humidifier::get_humidity() { return humidity; }

void Humidifier::set_humidity_correction(float new_correction) {
    humidity_correction = new_correction;
}

float Humidifier::get_humidity_correction() { return humidity_correction; }

void Humidifier::set_humidity_target(float new_target) { humidity_target = new_target; }

void Humidifier::update_pid_p_term(float new_p) { pid->update_p_term(new_p); }

void Humidifier::update_pid_i_term(float new_i) { pid->update_i_term(new_i); }

void Humidifier::update_pid_d_term(float new_d) { pid->update_d_term(new_d); }

void Humidifier::update_pid_terms(float new_p, float new_i, float new_d) {
    pid->update_pid_terms(new_p, new_i, new_d);
}

void Humidifier::update_pid_terms(pid_terms_t new_pid_terms) {
    pid->update_pid_terms(new_pid_terms);
}

pid_terms_t Humidifier::get_pid_terms() { return pid->get_pid_terms(); }

bool Humidifier::routine(float humidity_target) {
    update_humidity();

    if (isnan(humidity)) {
        return false;
    }

    // Reset PID in case the temperature target changes
    if (prev_humidity_target != humidity_target) {
        pid->reset();
        prev_humidity_target = humidity_target;
    }

    // Calculate PID output for servo

    return true;
}
