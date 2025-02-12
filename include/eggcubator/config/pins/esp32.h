#ifndef PINS_ESP32_H
#define PINS_ESP32_H

#define BOARD_ESP32

// Water level sensor pin (not yet implemented)
#define WATER_LEVEL_SENSOR_PIN 1

// Fan pin (not yet implemented)
#define FAN_PIN 10

// Heater pin
#define HEATER_PIN 15

// Thermistor pin
#define HEATER_SENSOR_PIN 34  // Thermistor

// DHT sensor pin
#define HUMIDIFIER_SENSOR_PIN 0

// Servo pin (not yet implemented)
#define HUMIDIFIER_SERVO_PIN 11

// Motors pins
#define MOTOR_PIN 9  // Deprecated in favor of stepper motor
#define MOTOR_IN1 27
#define MOTOR_IN2 26
#define MOTOR_IN3 25
#define MOTOR_IN4 33

// Display pins
#define UI_I2C_SCK_PIN 22
#define UI_I2C_SDA_PIN 21

// Speaker pin
#define UI_SPEAKER_PIN 18

// Rotary encoder pins
#define UI_ENCODER_CLK_PIN 4
#define UI_ENCODER_DT_PIN 16
#define UI_ENCODER_SW_PIN 17

#endif  // !PINS_ESP32_H
