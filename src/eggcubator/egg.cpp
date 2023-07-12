#include <eggcubator/egg.h>

static egg_t chicken_egg = {EGG_CHICKEN_TYPE,
                            EGG_CHICKEN_INCUBATION_PERIOD,
                            EGG_CHICKEN_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_START_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_STOP_MOTOR_ROTATION_PERIOD,
                            EGG_CHICKEN_TARGET_TEMP,
                            EGG_CHICKEN_TARGET_HUMD};

static egg_t quail_egg = {EGG_QUAIL_TYPE,
                          EGG_QUAIL_INCUBATION_PERIOD,
                          EGG_QUAIL_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_START_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_STOP_MOTOR_ROTATION_PERIOD,
                          EGG_QUAIL_TARGET_TEMP,
                          EGG_QUAIL_TARGET_HUMD};

static egg_t duck_egg = {EGG_DUCK_TYPE,
                         EGG_DUCK_INCUBATION_PERIOD,
                         EGG_DUCK_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_START_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_STOP_MOTOR_ROTATION_PERIOD,
                         EGG_DUCK_TARGET_TEMP,
                         EGG_DUCK_TARGET_HUMD};

static egg_t turkey_egg = {EGG_TURKEY_TYPE,
                           EGG_TURKEY_INCUBATION_PERIOD,
                           EGG_TURKEY_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_START_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_STOP_MOTOR_ROTATION_PERIOD,
                           EGG_TURKEY_TARGET_TEMP,
                           EGG_TURKEY_TARGET_HUMD};

static egg_t goose_egg = {EGG_GOOSE_TYPE,
                          EGG_GOOSE_INCUBATION_PERIOD,
                          EGG_GOOSE_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_START_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_STOP_MOTOR_ROTATION_PERIOD,
                          EGG_GOOSE_TARGET_TEMP,
                          EGG_GOOSE_TARGET_HUMD};

static egg_t pigeon_egg = {EGG_PIGEON_TYPE,
                           EGG_PIGEON_INCUBATION_PERIOD,
                           EGG_PIGEON_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_START_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_STOP_MOTOR_ROTATION_PERIOD,
                           EGG_PIGEON_TARGET_TEMP,
                           EGG_PIGEON_TARGET_HUMD};

egg_t *get_chicken_egg_config() { return &chicken_egg; }
void update_chicken_egg_config(egg_t egg) { chicken_egg = egg; }

egg_t *get_quail_egg_config() { return &quail_egg; }
void update_quail_egg_config(egg_t egg) { quail_egg = egg; }

egg_t *get_duck_egg_config() { return &duck_egg; }
void update_duck_egg_config(egg_t egg) { duck_egg = egg; }

egg_t *get_turkey_egg_config() { return &turkey_egg; }
void update_turkey_egg_config(egg_t egg) { quail_egg = egg; }

egg_t *get_goose_egg_config() { return &goose_egg; }
void update_goose_egg_config(egg_t egg) { quail_egg = egg; }

egg_t *get_pigeon_egg_config() { return &pigeon_egg; }
void update_pigeon_egg_config(egg_t egg) { quail_egg = egg; }

void print_egg_config(egg_t config) {
    Serial.print("egg type: ");
    Serial.println(config.type);
    Serial.print("egg incubation: ");
    Serial.println(config.incubation_days);
    Serial.print("rotation: ");
    Serial.println(config.eggs_rotation_period);
    Serial.print("start motor: ");
    Serial.println(config.start_of_motor_rotation);
    Serial.print("end motor: ");
    Serial.println(config.end_of_motor_rotation);
    Serial.print("egg temp: ");
    Serial.println(config.target_temp);
    Serial.print("egg humd: ");
    Serial.println(config.target_humd);
}
