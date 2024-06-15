# 🥚 Eggcubator

Eggcubator is a controller (**made for ESP32 boards**) for the incubation period of eggs of various types.
The main goals of this controller for the moment is to support temperature control,
egg rotation and the humidity inside the incubator, as this plays a crucial role.

> [!IMPORTANT]
> This project is currently under development and is not stable yet. Therefore,
> none of the features mentioned above might not yet be implemented.

## TO-DO List

- [ ] Core
  - [ ] PID Controller
  - [ ] Thermostat -> Controls the Heater MOSFET
  - [ ] Humidistat -> Controls the Servo to open/close a vent
  - [ ] Rotary Encoder Driver -> Used for UI Navigation
  - [ ] Servo Motor Controller
  - [ ] Speaker Driver
  - [ ] Clock/Timer Implementation -> used to control incubation period and motor rotations
  - [ ] Bridge the gap of U2g8 library for Oled screen
- [ ] UI
  - [ ] Menu Builder
  - [ ] Menu Navigation

## Dependencies

- [esp-idf](https://github.com/espressif/esp-idf)

## Build

1. `edf.py set-target esp32s3`
1. `edf.py menuconfig`
1. `edf.py -p PORT flash`
