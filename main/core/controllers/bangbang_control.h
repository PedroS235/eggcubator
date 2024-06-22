#ifndef BANGBANG_CONTROL_H
#define BANGBANG_CONTROL_H

#include "esp_err.h"

typedef struct bangbang_config {
  float min_output;
  float max_output;
} bangbang_config_t;

typedef struct bangbang_handle {
  bangbang_config_t config;
} bangbang_handle_t;

esp_err_t bangbang_control_create(bangbang_config_t *config,
                                  bangbang_handle_t *ret_bangbang);
esp_err_t bangbang_compute(bangbang_handle_t *bangbang, float setpoint,
                           float curr_value, float *correction);

#endif // !BANGBANG_CONTROL_H
