#ifndef EGG_H
#define EGG_H
#include <cstdint>

/*
 * Egg types:
 * 0: Chicken
 * 1: Quail
 * 2: Duck
 * 3: Turkey
 * 4: Goose
 * 5: Pigeon
 */

/**
 * @brief Struct representing the required information about an egg
 *
 * @param type: type of the egg which it represents
 * @param incubation_days: duration of the incubation in days
 * @param eggs_rotation_period: interval between rotations (in hours)
 * @param start_of_motor_rotation: day of incubation when the eggs should start rotating
 * @param end_of_motor_rotation: day of incubation when the eggs should stop rotating
 * @param target_temp: the desired targeted temperature
 * @param target_humd: the desired targeted humidity
 */
typedef struct {
    uint8_t type;
    uint8_t incubation_days;
    uint8_t eggs_rotation_period;
    uint8_t start_of_motor_rotation;
    uint8_t end_of_motor_rotation;
    float target_temp;
    float target_humd;
} egg_t;

#endif  // !EGG_H
