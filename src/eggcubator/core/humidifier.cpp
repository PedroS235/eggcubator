#include "eggcubator/core/humidifier.h"

#include "eggcubator/config/configuration.h"

Humidifier::Humidifier(unsigned long humidity_reading_interval_,
                       float humidity_correction_)
    : humidity(NAN),
      humidity_target(0),
      prev_humidity_target(0),
      last_humidity_reading_time(0) {
    sensor = new DHT(HUMIDIFIER_SENSOR_PIN, HUMIDIFIER_SENSOR_TYPE);

    pid_config = {.kp = HUMIDIFIER_PID_KP,
                  .ki = HUMIDIFIER_PID_KI,
                  .kd = HUMIDIFIER_PID_KD,
                  .min_output = 0,
                  .max_output = 255,
                  .min_integral = 0,
                  .max_integral = 100};

    pid = new PidControl(&pid_config);

    humidity_reading_interval = humidity_reading_interval_;
    humidity_correction = humidity_correction_;
    sensor->begin();
}

float Humidifier::get_humidity() { return humidity; }
float Humidifier::get_target() { return humidity_target; }

void Humidifier::set_humidity_correction(float new_correction) {
    log_v("Setting new humidity correction from %f to %f",
          humidity_correction,
          new_correction);
    humidity_correction = new_correction;
}

float Humidifier::get_humidity_correction() { return humidity_correction; }

void Humidifier::set_humidity_target(float new_target) {
    log_v("Setting new humidity target from %f to %f", humidity_target, new_target);
    humidity_target = new_target;
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

    pid_config.kp = new_p;
    pid_config.ki = new_i;
    pid_config.kd = new_d;
    pid->update_pid_config(&pid_config);
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

    pid_config.kp = new_config.kp;
    pid_config.ki = new_config.ki;
    pid_config.kd = new_config.kd;
    pid_config.min_output = new_config.min_output;
    pid_config.max_output = new_config.max_output;
    pid_config.min_integral = new_config.min_integral;
    pid_config.max_integral = new_config.max_integral;
    pid->update_pid_config(&new_config);
}

void Humidifier::update_pid_kp(float new_p) {
    pid_config.kp = new_p;
    pid->update_pid_config(&pid_config);
}
void Humidifier::update_pid_ki(float new_i) {
    pid_config.ki = new_i;
    pid->update_pid_config(&pid_config);
}
void Humidifier::update_pid_kd(float new_d) {
    pid_config.kd = new_d;
    pid->update_pid_config(&pid_config);
}

pid_config_t Humidifier::get_pid_terms() { return pid->get_pid_config(); }

void Humidifier::log_stats() {
    log_i("Humidifier: %f/%f°C", humidity, humidity_target);
}

void Humidifier::task(void *pvParameters) {
    for (;;) {
        log_v("Ticking humidifier");

        const float reading = sensor->readHumidity();
        if (!isnan(reading)) {
            humidity = reading + humidity_correction;
        } else {
            humidity = NAN;
        }

        log_v("Humidity Reading %f", humidity);

        // Reset PID in case the temperature target changes
        if (prev_humidity_target != humidity_target) {
            pid->reset();
            prev_humidity_target = humidity_target;
        }

        // Calculate PID output for servo

        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Adjust the delay as needed
    }
}
