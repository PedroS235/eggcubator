#ifndef EGG_FACTORY
#define EGG_FACTORY

#include <Arduino.h>

#include "eggcubator/config/configuration.h"

typedef struct {
    uint8_t type;
    uint8_t incubation_days;
    uint8_t eggs_rotation_period;
    uint8_t start_of_motor_rotation;
    uint8_t end_of_motor_rotation;
    float target_temp;
    float target_humd;
} egg_t;

class EggFactory {
   public:
    static egg_t createChickenEgg() {
        log_d("Creating Chicken Egg.");
        return {EGG_CHICKEN_TYPE,
                EGG_CHICKEN_INCUBATION_PERIOD,
                EGG_CHICKEN_MOTOR_ROTATION_PERIOD,
                EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD,
                EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD,
                EGG_CHICKEN_TARGET_TEMP,
                EGG_CHICKEN_TARGET_HUMD};
    }

    static egg_t createQuailEgg() {
        log_d("Creating Quail Egg.");
        return {EGG_QUAIL_TYPE,
                EGG_QUAIL_INCUBATION_PERIOD,
                EGG_QUAIL_MOTOR_ROTATION_PERIOD,
                EGG_QUAIL_START_MOTOR_ROTATION_PERIOD,
                EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD,
                EGG_QUAIL_TARGET_TEMP,
                EGG_QUAIL_TARGET_HUMD};
    }

    static egg_t createDuckEgg() {
        log_d("Creating Duck Egg.");
        return {EGG_DUCK_TYPE,
                EGG_DUCK_INCUBATION_PERIOD,
                EGG_DUCK_MOTOR_ROTATION_PERIOD,
                EGG_DUCK_START_MOTOR_ROTATION_PERIOD,
                EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD,
                EGG_DUCK_TARGET_TEMP,
                EGG_DUCK_TARGET_HUMD};
    }

    static egg_t createTurkeyEgg() {
        log_d("Creating Turkey Egg.");
        return {EGG_TURKEY_TYPE,
                EGG_TURKEY_INCUBATION_PERIOD,
                EGG_TURKEY_MOTOR_ROTATION_PERIOD,
                EGG_TURKEY_START_MOTOR_ROTATION_PERIOD,
                EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD,
                EGG_TURKEY_TARGET_TEMP,
                EGG_TURKEY_TARGET_HUMD};
    }

    static egg_t createGooseEgg() {
        log_d("Creating Goose Egg.");
        return {EGG_GOOSE_TYPE,
                EGG_GOOSE_INCUBATION_PERIOD,
                EGG_GOOSE_MOTOR_ROTATION_PERIOD,
                EGG_GOOSE_START_MOTOR_ROTATION_PERIOD,
                EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD,
                EGG_GOOSE_TARGET_TEMP,
                EGG_GOOSE_TARGET_HUMD};
    }

    static egg_t createPigeonEgg() {
        log_d("Creating Pigeon Egg.");
        return {EGG_PIGEON_TYPE,
                EGG_PIGEON_INCUBATION_PERIOD,
                EGG_PIGEON_MOTOR_ROTATION_PERIOD,
                EGG_PIGEON_START_MOTOR_ROTATION_PERIOD,
                EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD,
                EGG_PIGEON_TARGET_TEMP,
                EGG_PIGEON_TARGET_HUMD};
    }

    static egg_t createEggFromIdx(int idx) {
        switch (idx) {
            case 0:
                return createChickenEgg();
            case 1:
                return createQuailEgg();
            case 2:
                return createDuckEgg();
            case 3:
                return createTurkeyEgg();
            case 4:
                return createGooseEgg();
            case 5:
                return createPigeonEgg();
            default:
                return createChickenEgg();
        }
    }
};

#endif  // !EGG_FACTORY
