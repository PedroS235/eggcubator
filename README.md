# 🥚 Eggcubator

Eggcubator is a controller (**made for ESP32 boards**) for the incubation period of eggs of various types.
The main goals of this controller for the moment is to support temperature control,
egg rotation and the humidity inside the incubator, as this plays a crucial role.

> [!IMPORTANT]
> This project is currently under development and is not stable yet. Therefore,
> none of the features mentioned above might not yet be implemented.

## Project Structure

```
eggcubator/src
  /core
    - incubation.rs
    - pid_control.rs
    - heater.rs
    - motor.rs
    - servo.rs
    - humidifier.rs
    - timer_control.rs
  /drivers
    - rotary_encoder.rs
    - thermistor.rs
    - speaker.h/cpp
    - dht.rs
  /web
    - server.rs
  /ui
    - menu.rs
  /extras
    - led_status.h/cpp
    - pid_calibration.h/cpp
```

## Architecture

### Incubation

- **Input**: Type of egg to incubate
- **Output**: Control of incubation period. Uses `heater`, `humidifier`, `motor` and `timer_control`

### Heater

- **Input**: Target Temperature
- **Output**: PWM which controls the heater element. Uses the `pid_control` and the `termistor`

### Humidifier

- **Input**: Target Humidity
- **Output**: Controls the servo motor. Uses the `servo` and `dht`

### Motor

- **Input**: On/Off
- **Output**: Controls the motor if its on or off. Uses the `motor`

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

- [esp-rs](https://docs.esp-rs.org/book/)

## Build && Flash

1. `cargo run`
