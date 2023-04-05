#ifndef EGG_H
#define EGG_H
#include <cstdint>

/*
 * Egg types:
 * 0: Chicken
 * 1: Quail
 * 2: Pigeon
 */

typedef struct {
    uint8_t type;
    uint8_t incubation_period;
    uint8_t motor_rotation_duration;
    uint8_t motor_rotation_period;
    uint8_t start_motor_rotation_period;  // relative to the beginging of inucabtion
    uint8_t stop_motor_rotation_period;   // relative to the end of incubation
    float target_temp;
    float target_humd;
} egg_t;

#endif  // !EGG_H
