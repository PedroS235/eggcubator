#include "core/controllers/bangbang_control.h"
#include "esp_check.h"

static const char *TAG = "Bang-Bang Control";

esp_err_t bangbang_control_create(bangbang_config_t *config,
                                  bangbang_handle_t *ret_bangbang) {
  esp_err_t ret = ESP_OK;
  bangbang_handle_t *bangbang = NULL;
  ESP_GOTO_ON_FALSE(config, ESP_ERR_INVALID_ARG, err, TAG,
                    "Config argument is not valid");
  bangbang = calloc(1, sizeof(bangbang_handle_t));
  ESP_GOTO_ON_FALSE(bangbang, ESP_ERR_NO_MEM, err, TAG, "ESP out of memory");
  bangbang->config = *config;

  *ret_bangbang = *bangbang;
  return ret;

err:
  if (bangbang)
    free(bangbang);
  return ret;
}

esp_err_t bangbang_compute(bangbang_handle_t *bangbang, float setpoint,
                           float curr_value, float *correction) {
  const float error = setpoint - curr_value;

  if (error > 0) {
    *correction = bangbang->config.max_output;
  } else {
    *correction = bangbang->config.min_output;
  }

  return ESP_OK;
}
