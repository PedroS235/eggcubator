#ifndef PINS_ESP32_S3_H
#define PINS_ESP32_S3_H

#define BOARD_ESP32_S3

// Water level sensor pin (not yet implemented)
#define WATER_LEVEL_SENSOR_PIN 1

// Fan pin (not yet implemented)
#define FAN_PIN 10

// Heater pin
#define HEATER_PIN 7

// Thermistor pin
#define HEATER_SENSOR_PIN 6  // Thermistor

// DHT sensor pin
#define HUMIDIFIER_SENSOR_PIN 2

// Servo pin (not yet implemented)
#define HUMIDIFIER_SERVO_PIN 11

// Motors pins
#define MOTOR_PIN 9  // Deprecated in favor of stepper motor
#define MOTOR_IN1 8
#define MOTOR_IN2 9
#define MOTOR_IN3 10
#define MOTOR_IN4 11

// Display pins
#define UI_I2C_SCK_PIN 12
#define UI_I2C_SDA_PIN 13

// Speaker pin
#define UI_SPEAKER_PIN 2

// Rotary encoder pins
#define UI_ENCODER_CLK_PIN 3
#define UI_ENCODER_DT_PIN 4
#define UI_ENCODER_SW_PIN 5

#endif  // !PINS_ESP32_S3_H
