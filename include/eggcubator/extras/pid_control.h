/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
 */

#ifndef PID_CONTROL_H
#define PID_CONTROL_H

typedef struct {
    float kp;
    float ki;
    float kd;
    float min_output;
    float max_output;
    float min_integral;
    float max_integral;
} pid_config_t;

/**
 * @brief Simple PID controller class which can be be used for general purpose
 */
class PidControl {
   private:
    pid_config_t *_config;
    float _error_sum;
    float _prev_error;

   public:
    /**
     * @brief Constructor for the class PID
     *
     * @param config is the default configuration for the pid
     *
     */
    PidControl(pid_config_t *config);

    void update_pid_config(pid_config_t *config);
    pid_config_t get_pid_config();

    /**
     * @brief Resets the errors
     */
    void reset();

    /**
     * @brief Compute the correction to be made in relation of the current
     * measured term and the desired setpoint
     *
     * @param setpoint is the desired setpoint
     * @param current_term is the current measured value
     *
     * @return PWM value (min_output-max_output) which correlates to the correction made
     */
    float compute(float setpoint, float current_term);
};

#endif  // !PID_CONTROL_H

/*
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
