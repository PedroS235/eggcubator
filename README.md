# EggCubator

EggCubator is an Arduino-based program that controls the incubation period of
chicken eggs (or any other type of egg). It uses a set of sensors, a servo motor,
a motor to rotate the eggs, a heater, a fan, and an OLED screen to monitor and
regulate temperature, humidity, and other factors that affect egg incubation.

**DISCLAIMER: This project is currently under development!**

## Getting Started

To use EggCubator, you will need an Arduino board (ESP32 is recommended), the
sensors, motors and other components which can be found in the [Components](#components) section.

## Prerequisites

- PlatformIO

## Installation

1. Download or clone the EggCubator repository.
1. `cd eggcubator`
1. Build the package using either `pio run --target  upload` or using the build icon in VSCode
1. Connect the components as shown in the wiring diagram.
1. Upload the code to your Arduino board.

## Components

- ESP32 (or other compatible Arduino board)
- OLED screen (128x64)
- DHT22 sensor (for temperature and humidity)
- Servo motor (for vent control) **[optional]**
- MOSFETs (for heater, fan, and motor control)
- Rotary encoder
- Speaker **[optional]**

## Software Architecture

EggCubator uses an object-oriented approach to programming, with separate classes for each major component or functionality:

Thermostat: responsible for controlling the temperature
Humidistat: responsible for controlling the humidity
Timer: responsible for monitoring the incubation time
Display: responsible for controlling the OLED screen
PID: responsible for the temperature control algorithm
ServoController: responsible for controlling the vent servo
MotorController: responsible for controlling the egg rotation motor
EEPROMManager: responsible for storing and retrieving settings from EEPROM
Routine: responsible for controlling the logic of the incubation period

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please create a new issue or pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
