<div align="center"><h1>🥚 Eggcubator</h1></div>

**Eggcubator** is a controller (**designed for ESP32 boards**) for the incubation period of eggs of various types.
The main goals of this controller for the moment is to support temperature control,
egg rotation and the humidity inside the incubator, as this plays a crucial role.

> [!IMPORTANT]
> This project is currently under development and is not stable yet. Therefore,
> none of the features mentioned above might not yet be implemented.

### Prerequisites

- PlatformIO (Tool to upload the code to the board)

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

## TO-DO

### Higher Priority

- [x] Implement a Thermistor Driver
- [x] Change Thermostat to be named heater
- [x] Use the thermistor for the heater instead of DHT
- [x] Implement a better timer management using esp_timer (keeping current implementation)
- [ ] Implement a Humidifier
- [ ] Implement Logging for error and debug

### Low Priority

- [x] Possibly use FreeRTOS for having a scheduler
- [x] Use esp_log instead
