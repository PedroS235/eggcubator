#include "core/controllers/pid_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

void app_main(void) {
  pid_handle_t pid;
  pid_config_t config = {.kp = 1,
                         .kd = 1,
                         .ki = 1,
                         .max_output = 255,
                         .min_output = 0,
                         .max_integral = 125,
                         .min_integral = 0};
  pid_control_create(&config, &pid);

  float curr = 0;
  float correction;

  while (1) {
    pid_compute(&pid, 40, curr, false, &correction);
    printf("Setpoint: %f | Current value: %f | Correction: %f\n", 40.0, curr,
           correction);
    curr += 1;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
