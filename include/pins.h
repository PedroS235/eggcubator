/*
 * This file contains the GPIO pins which are associated with each sensor
 * or component connected to the board.
 * You may change any of the defined pins to your specific pins.
 */

#ifndef PINS_H
#define PINS_H

// DHT22 data pin
#define PIN_DHT 32

// Heater MOSFET
#define PIN_HEATER 19

// Fan MOSFET
// #define PIN_FAN -1

// Eggs rotation motor
#define PIN_MOTOR 23

// Speaker pin
#define PIN_BUZZER 2

// Rotary encoder pins
#define PIN_ENCODER_CLK 25
#define PIN_ENCODER_DT 26
#define PIN_ENCODER_SW 27

// Servo data pins
// #define PIN_SERVO

// I2C PINS (Don't change if using a ESP32)
#define PIN_I2C_SDA 21
#define PIN_I2C_SCK 22

#endif // !PINS_H
