# 🥚 Eggcubator

Eggcubator is a controller (**made for ESP32 boards**) for the incubation period of eggs of various types.
The main goals of this controller for the moment is to support temperature control,
egg rotation and the humidity inside the incubator, as this plays a crucial role.

> [!IMPORTANT]
> This project is currently under development and is not stable yet. Therefore,
> none of the features mentioned above might not yet be implemented.

## Project Structure

```
eggcubator/
  /core
    - incubation.h/cpp
    /controllers
      - pid_control.h/cpp
      - bangbang_control.h/cpp
    /actuators
      - heater.h/cpp
      - humidifier.h/cpp
    /sensors
      - rotary_encoder.h/cpp
      - thermostat.h/cpp
      - dht.h/cpp
    /timing (Might not need)
      - clock_timer.h/cpp
  /web
    - server.h/cpp
  /ui
    - oled_screen_interface.h/cpp
    - menu_builder.h/cpp
    - menu_navigation.h/cpp
  /extras
    - speaker.h/cpp
    - led_status.h/cpp
    - pid_calibration.h/cpp
```

## PINs

- `GPIO_01`: Water Level Sensor
- `GPIO_02`: DHT11/22
- `GPIO_03`: Rotary Encoder CLK
- `GPIO_04`: Rotary Encoder DT
- `GPIO_05`: Rotary Encoder SW
- `GPIO_06`: BUZZER
- `GPIO_07`: THERMISTOR
- `GPIO_O8`: HEATER
- `GPIO_O9`: MOTOR
- `GPIO_10`: FAN
- `GPIO_11`: SERVO
- `GPIO_12`: OLED_SCK
- `GPIO_13`: OLED_SDA

## Dependencies

- [esp-idf](https://github.com/espressif/esp-idf)

## Build

1. `edf.py set-target esp32s3`
1. `edf.py menuconfig`
1. `edf.py -p PORT flash`
