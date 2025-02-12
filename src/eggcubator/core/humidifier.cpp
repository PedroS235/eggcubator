#include "eggcubator/core/humidifier.h"

#include "eggcubator/config/configuration.h"

Humidifier::Humidifier(unsigned long humidity_reading_interval_,
                       float humidity_correction_)
    : _humidity(NAN),
      _humidity_target(0),
      _prev_humidity_target(0),
      _last_humidity_reading_time(0) {
    _sensor = new DHT(HUMIDIFIER_SENSOR_PIN, HUMIDIFIER_SENSOR_TYPE);

    _pid_config = {.kp = HUMIDIFIER_PID_KP,
                   .ki = HUMIDIFIER_PID_KI,
                   .kd = HUMIDIFIER_PID_KD,
                   .min_output = 0,
                   .max_output = 255,
                   .min_integral = 0,
                   .max_integral = 100};

    _pid = new PidControl(&_pid_config);

    humidity_reading_interval_ = humidity_reading_interval_;
    humidity_correction_ = humidity_correction_;
    _sensor->begin();
}

float Humidifier::get_humidity() { return _humidity; }
float Humidifier::get_target() { return _humidity_target; }

void Humidifier::set_humidity_correction(float new_correction) {
    log_v("Setting new humidity correction from %f to %f",
          humidity_correction,
          new_correction);
    _humidity_correction = new_correction;
}

float Humidifier::get_humidity_correction() { return _humidity_correction; }

void Humidifier::set_humidity_target(float new_target) {
    log_v("Setting new humidity target from %f to %f", humidity_target, new_target);
    _humidity_target = new_target;
}

void Humidifier::update_pid_terms(float new_p, float new_i, float new_d) {
    log_v(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        pid_config.kp,
        pid_config.ki,
        pid_config.kd,
        new_p,
        new_i,
        new_d);

    _pid_config.kp = new_p;
    _pid_config.ki = new_i;
    _pid_config.kd = new_d;
    _pid->update_pid_config(&_pid_config);
}

void Humidifier::update_pid_terms(pid_config_t new_config) {
    log_v(
        "Updating PID values | from: kp: %f, ki: %f, kd: %f - to: kp: %f, ki: %f, kd: "
        "%f",
        pid_config.kp,
        pid_config.ki,
        pid_config.kd,
        new_config.kp,
        new_config.ki,
        new_config.kd);

    _pid_config.kp = new_config.kp;
    _pid_config.ki = new_config.ki;
    _pid_config.kd = new_config.kd;
    _pid_config.min_output = new_config.min_output;
    _pid_config.max_output = new_config.max_output;
    _pid_config.min_integral = new_config.min_integral;
    _pid_config.max_integral = new_config.max_integral;
    _pid->update_pid_config(&new_config);
}

void Humidifier::update_pid_kp(float new_p) {
    _pid_config.kp = new_p;
    _pid->update_pid_config(&_pid_config);
}
void Humidifier::update_pid_ki(float new_i) {
    _pid_config.ki = new_i;
    _pid->update_pid_config(&_pid_config);
}
void Humidifier::update_pid_kd(float new_d) {
    _pid_config.kd = new_d;
    _pid->update_pid_config(&_pid_config);
}

pid_config_t Humidifier::get_pid_terms() { return _pid->get_pid_config(); }

void Humidifier::log_stats() {
    log_i("Humidifier: %f/%f°C", _humidity, _humidity_target);
}

void Humidifier::task(void *pvParameters) {
    for (;;) {
        log_v("Ticking humidifier");

        const float reading = _sensor->readHumidity();
        if (!isnan(reading)) {
            _humidity = reading + _humidity_correction;
        } else {
            _humidity = NAN;
        }

        log_v("Humidity Reading %f", humidity);

        // Reset PID in case the temperature target changes
        if (_prev_humidity_target != _humidity_target) {
            _pid->reset();
            _prev_humidity_target = _humidity_target;
        }

        // Calculate PID output for servo

        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Adjust the delay as needed
    }
}
