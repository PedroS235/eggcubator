#ifndef MENUS_H
#define MENUS_H

#include <Arduino.h>
inline const char *main_menu[] = {"Go Back", "Incubate", "Preheat", "Settings"};
inline uint8_t main_menu_size = 4;

inline const char *incubate_menu[] =
    {"Go Back", "Chicken", "Quail", "Duck", "Turkey", "Goose", "Pigeon"};
inline uint8_t incubate_menu_size = 7;

inline const char *preheat_menu[] =
    {"Go Back", "Manual", "Chicken", "Quail", "Duck", "Turkey", "Goose", "Pigeon"};
inline uint8_t preheat_menu_size = 7;

inline const char *eggs_settings_menu[] =
    {"Go Back", "Chicken", "Quail", "Duck", "Turkey", "Goose", "Pigeon"};
inline uint8_t eggs_settings_menu_size = 7;

inline const char *settings_menu[] = {"Go Back",
                                      "Calibrate",
                                      "Eggs settings",
                                      "Save",
                                      "Reset"};
inline uint8_t settings_menu_size = 5;

inline const char *calibrate_menu[] = {"Go Back",
                                       "Temperature",
                                       "Humidity",
                                       "PID",
                                       "Motor duration"};
inline uint8_t calibrate_menu_size = 5;

inline const char *egg_config_menu[] = {"Go Back",
                                        "Target temp",
                                        "Target Humd",
                                        "Period",
                                        "Rot period",
                                        "Start of rot",
                                        "End of rot"};
inline uint8_t egg_config_menu_size = 7;

inline const char *pid_menu[] = {"Go Back", "kp", "ki", "kd"};
inline uint8_t pid_menu_size = 4;

inline const char *tune_menu[] = {"Go Back",
                                  "Target temp",
                                  "Target Humd",
                                  "Rot period"};
inline uint8_t tune_menu_size = 4;

#endif  // !MENUS_H
