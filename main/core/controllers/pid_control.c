#include "core/controllers/pid_control.h"
#include "esp_check.h"
#include <sys/param.h>

static const char *TAG = "PID Control";

esp_err_t pid_control_create(pid_config_t *config, pid_handle_t *ret_pid) {
  esp_err_t ret = ESP_OK;
  pid_handle_t *pid = NULL;
  ESP_GOTO_ON_FALSE(config, ESP_ERR_INVALID_ARG, err, TAG,
                    "Config argument is not valid");
  pid = calloc(1, sizeof(pid_handle_t));
  ESP_GOTO_ON_FALSE(pid, ESP_ERR_NO_MEM, err, TAG, "ESP out of memory");
  ESP_GOTO_ON_ERROR(pid_update_config(config, pid), err, TAG,
                    "Failed to update PID config");

  *ret_pid = *pid;
  return ret;

err:
  if (pid)
    free(pid);
  return ret;
}

esp_err_t pid_update_config(pid_config_t *config, pid_handle_t *pid) {
  ESP_RETURN_ON_FALSE(config, ESP_ERR_INVALID_ARG, TAG,
                      "Config parameter is not valid");
  pid->config = *config;
  return ESP_OK;
}

esp_err_t pid_reset(pid_handle_t *pid) {
  ESP_RETURN_ON_FALSE(pid, ESP_ERR_INVALID_ARG, TAG,
                      "Pid argument is not valid");
  pid->prev_error = 0;
  pid->error_sum = 0;
  return ESP_OK;
}

esp_err_t pid_compute(pid_handle_t *pid, float setpoint, float curr_value,
                      bool reset, float *correction) {

  ESP_RETURN_ON_FALSE(pid, ESP_ERR_INVALID_ARG, TAG,
                      "PID argument is not valid");

  const float error = setpoint - curr_value;

  // Eliminate possible noise on the integral term.
  if ((error == 0 && setpoint == 0) || reset) {
    ESP_RETURN_ON_ERROR(pid_reset(pid), TAG, "Failed to reset PID");
  }

  // Integral Anti-windup
  pid->error_sum = MIN(pid->error_sum + error, pid->config.max_integral);
  pid->error_sum = MAX(pid->error_sum + error, pid->config.min_integral);

  const float p = pid->config.kp * error;
  const float i = pid->config.ki * pid->error_sum;
  const float d = pid->config.kd * (error - pid->prev_error);

  *correction = MIN(p + i + d, pid->config.max_output);
  *correction = MAX(p + i + d, pid->config.min_output);

  pid->prev_error = error;

  return ESP_OK;
}
