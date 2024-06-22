#include "core/controllers/bangbang_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

void app_main(void) {
  bangbang_handle_t bangbang;
  bangbang_config_t config = {
      .max_output = 255,
      .min_output = 0,
  };
  bangbang_control_create(&config, &bangbang);

  float curr = 0;
  float correction;

  while (1) {
    bangbang_compute(&bangbang, 20, curr, &correction);
    printf("Setpoint: %f | Current value: %f | Correction: %f\n", 40.0, curr,
           correction);
    curr += 1;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
