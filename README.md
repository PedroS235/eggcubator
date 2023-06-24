# EggCubator

EggCubator is an Arduino-based program that controls the incubation period of
chicken eggs (or any other type of egg). It's main target is to control the
temperature inside the incubator, which uses a PID controller for controlling an
heating source. In addition, the controller is also able to rotate a DC motor
in order to rotate the eggs every x amount of time. Furthermore, the controller
will also be able to control the humidity inside the incubator, by controlling
and opening using a servo motor, letting fresh air enter or not. This however,
is just theory and I cannot be sure that it will be able to adjust the humidity.
Therefore, this must still be tested.

This controller, is targeted to be used with an OLED screen, which is used to
navigate between the different menus available, and also change some configuration
parameters on the go, without the need of flashing the firmware to the controller board.

As of now, the current state of the controller is still very limited, and it was
not tested yet. Nevertheless, it should now be able to control the incubation of
any of the eggs configarations available. Before using it, the PID gains will need
to be tuned, in order for the temperature to be consistent. Otherwise, the temperature
will most likely fluctuate quite a lot. However, I cannot yet give a guide on how to
perform such tune, as I have not yet tested on the real thing. In addition, I have
not yet implemented a watchdog for the heater, and thus if the temperature sensor
is by any change damaged, and the heater is trying to achieve the desired temperature,
it will not stop until it reaches it. For this reason, **the controller will not stop at this point**.

**DISCLAIMER: This project is currently under development! If you plan to use this, be very careful!**

## Table of Contents

- [Installation](installation)

## Installation

To use EggCubator, you will need an Arduino board (ESP32 is recommended), the
sensors, motors and other components which can be found in the [Bill of Materieals](#bill-of-materials) section.

With all the components gathered, you will need to connect them to the your
board of choice. In case you are using an ESP32 board and want to stick the
default connections, you can follow the schematic in [here](#schematic).

TODO: Finish this section

### Prerequisites

- PlatformIO (Tool to upload the code to the board)
- The core components

## Bill of Materials

- ESP32 (or other compatible Arduino board)
- OLED screen (128x64)
- DHT22 sensor (for temperature and humidity)
- Servo motor (for vent control) **[optional]**
- MOSFETs (for heater, fan, and motor control)
- Rotary encoder
- Speaker **[optional]**
- TODO: To add the missing components

### schematic

TODO: Create a schematic

## Software Architecture

EggCubator uses an object-oriented approach to programming, with separate classes for each major component or functionality.
Each class that requires to be executed in every clock cycle, is equiped with a method called routine, which acts like an inner loop.
These methods are then called within the main loop.

From all the classes, there are a few that stand out, which are essential for the functionality of the controller. These are:

- **Thermostat**: Responsible of regulating the temperature inside the incubator.
- **IncubationRoutine**: Responsible of controlling the incubation cycles.
- **Humidstat**: Responsible of regulating the humidity inside the incubator.
- **EggcubatorGUI**: Responsible for controlling the GUI and managing the display.

## How it works

The process of incubating eggs is to place the eggs inside some chamber for a defined period of time at a constant temperature and humidity.
In addition, the eggs will need to be turned every x hours after some days after the start of incubation and before some days before the end of the incubation.

To achieve this, this controller uses a DHT22 sensor in order to measure both the temperature and humidity and MOSFETs which controls an heater, a fan and a motor.
Based on the temperature readings and the targeted temperature, the controller uses a PID loop in order to control the heater by regulating the voltage
of the heater applied. In addition, a fan is activated when the heater is on in order to mix the hot air inside the chamber. For the humidity, a servo is used,
where the goal is to control a vent which will either let fresh air enter the chanber or not.

Currenlty, in order to turn the eggs, this controller expects the use of a DC/AC motor, and is simply turned on or off. To control how much the eggs turn,
a duration is set which allows the eggs to be turned the same way every turn.

The EggCubator controller is also equipped with a display which is used as a GUI for the user and allows to customize some of the settings on the go, without the need
of re-uploading the code to the board over and over again a change is made, or needs to be made.
Furthermore, the screen also provides with realtime information about the current incubation in place, such as the current temperature,
humidity and a progress bar.

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please create a new issue or pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
