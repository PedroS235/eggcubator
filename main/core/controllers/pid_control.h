#ifndef PID_CONTROL
#define PID_CONTROL

#include "esp_err.h"
#include "stdbool.h"
#include "stdint.h"

typedef struct pid_config {
  float kp;
  float ki;
  float kd;
  float min_output;
  float max_output;
  float min_integral;
  float max_integral;
} pid_config_t;

typedef struct pid_handle {
  pid_config_t config;
  float prev_error;
  float error_sum;
} pid_handle_t;

esp_err_t pid_control_create(pid_config_t *config, pid_handle_t *ret_pid);
esp_err_t pid_update_config(pid_config_t *config, pid_handle_t *pid);
esp_err_t pid_compute(pid_handle_t *pid, float setpoint, float curr_value,
                      bool reset, float *correction);
esp_err_t pid_reset(pid_handle_t *pid);

#endif // !PID_CONTROL
