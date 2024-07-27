#ifndef FACTORY_H
#define FACTORY_H

#include "eggcubator/extras/pid_control.h"
#pragma once

#include "eggcubator/ui/language/language.h"
#include "eggcubator/ui/menu.h"

class MenuFactory {
   public:
    static Menu* createMainMenu() {
        MenuItem** mainMenuItems = new MenuItem*[4];
        mainMenuItems[0] = new MenuItem(GO_BACK_STR);
        mainMenuItems[1] = new MenuItem(INCUBATE_STR);
        mainMenuItems[2] = new MenuItem(PREHEAT_STR);
        mainMenuItems[3] = new MenuItem(SETTINGS_STR);
        return new Menu(mainMenuItems, 4);
    }

    static Menu* createIncubationMenu() {
        MenuItem** incubationMenuItems = new MenuItem*[7];
        incubationMenuItems[0] = new MenuItem(GO_BACK_STR);
        incubationMenuItems[1] = new MenuItem(CHICKEN_STR);
        incubationMenuItems[2] = new MenuItem(QUAIL_STR);
        incubationMenuItems[3] = new MenuItem(DUCK_STR);
        incubationMenuItems[4] = new MenuItem(TURKEY_STR);
        incubationMenuItems[5] = new MenuItem(GOOSE_STR);
        incubationMenuItems[6] = new MenuItem(PIGEON_STR);
        return new Menu(incubationMenuItems, 7);
    }

    static Menu* createPreheatMenu(float curr_target_temp) {
        MenuItem** preheatMenuItems = new MenuItem*[8];
        preheatMenuItems[0] = new MenuItem(GO_BACK_STR);
        preheatMenuItems[1] = new ValueMenuItem(MANUAL_STR, curr_target_temp);
        preheatMenuItems[2] = new MenuItem(CHICKEN_STR);
        preheatMenuItems[3] = new MenuItem(QUAIL_STR);
        preheatMenuItems[4] = new MenuItem(DUCK_STR);
        preheatMenuItems[5] = new MenuItem(TURKEY_STR);
        preheatMenuItems[6] = new MenuItem(GOOSE_STR);
        preheatMenuItems[7] = new MenuItem(PIGEON_STR);
        return new Menu(preheatMenuItems, 8);
    }

    static Menu* createSettingsMenu(float motor_rotation) {
        MenuItem** settingsMenuItems = new MenuItem*[6];
        settingsMenuItems[0] = new MenuItem(GO_BACK_STR);
        settingsMenuItems[1] = new MenuItem(HEATER_STR);
        settingsMenuItems[2] = new MenuItem(HUMIDIFIER_STR);
        settingsMenuItems[3] = new ValueMenuItem(MOTOR_ROTATION_STR, motor_rotation);
        settingsMenuItems[4] = new MenuItem(SAVE_STR);
        settingsMenuItems[5] = new MenuItem(RESET_STR);
        return new Menu(settingsMenuItems, 6);
    }

    static Menu* createHeaterMenu(pid_config_t pid_config, float temp_offset) {
        MenuItem** heaterMenuItems = new MenuItem*[5];
        heaterMenuItems[0] = new MenuItem(GO_BACK_STR);
        heaterMenuItems[1] = new ValueMenuItem("kp", pid_config.kp);
        heaterMenuItems[2] = new ValueMenuItem("ki", pid_config.ki);
        heaterMenuItems[3] = new ValueMenuItem("kd", pid_config.kd);
        heaterMenuItems[4] = new ValueMenuItem(TEMPERATURE_OFFSET_STR, temp_offset);
        return new Menu(heaterMenuItems, 5);
    }

    static Menu* createHumidifierMenu(pid_config_t pid_config, float humd_offset) {
        MenuItem** humidifierMenuItems = new MenuItem*[5];
        humidifierMenuItems[0] = new MenuItem(GO_BACK_STR);
        humidifierMenuItems[1] = new ValueMenuItem("kp", pid_config.kp);
        humidifierMenuItems[2] = new ValueMenuItem("ki", pid_config.ki);
        humidifierMenuItems[3] = new ValueMenuItem("kd", pid_config.kd);
        humidifierMenuItems[4] = new ValueMenuItem(HUMIDITY_OFFSET_STR, humd_offset);
        return new Menu(humidifierMenuItems, 5);
    }

    static Menu* createInIncubationMenu() {
        MenuItem** inIncubationMenuItems = new MenuItem*[3];
        inIncubationMenuItems[0] = new MenuItem(GO_BACK_STR);
        inIncubationMenuItems[1] = new MenuItem(TUNE_STR);
        inIncubationMenuItems[2] = new MenuItem(STOP_INCUBATION_STR);
        return new Menu(inIncubationMenuItems, 3);
    }

    static Menu* createInIncubationTuneMenu(float target_temp,
                                            float target_humd,
                                            float motor_rotation) {
        MenuItem** inIncubationTuneMenuItems = new MenuItem*[4];
        inIncubationTuneMenuItems[0] = new MenuItem(GO_BACK_STR);
        inIncubationTuneMenuItems[1] =
            new ValueMenuItem(TARGET_TEMPERATURE_STR, target_temp);
        inIncubationTuneMenuItems[2] =
            new ValueMenuItem(TARGET_HUMIDITY_STR, target_humd);
        inIncubationTuneMenuItems[3] =
            new ValueMenuItem(MOTOR_ROTATION_STR, motor_rotation);
        return new Menu(inIncubationTuneMenuItems, 4);
    }
};

#endif  // !FACTORY_H
