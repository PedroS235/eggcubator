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
} pid_terms_t;

/**
 * @brief Simple PID controller class which can be be used for general purpose
 */
class PID {
   private:
    pid_terms_t pid_terms;
    float error_sum;
    float prev_error;

   public:
    /**
     * @brief Constructor for the class PID
     *
     * @param kp_ is the proportional term
     * @param ki_ is the integral term
     * @param kd_ is the derivative term
     *
     */
    PID(float kp_, float ki_, float kd_);
    PID(pid_terms_t pid_terms_);

    /**
     * @brief Updates the current proportional term
     *
     * @param new_p is the new proportional term to be set
     */
    void update_p_term(float new_p);

    /**
     * @brief Updates the current integral term
     *
     * @param new_i is the new integral term to be set
     */
    void update_i_term(float new_i);

    /**
     * @brief Updates the current derivative term
     *
     * @param new_d is the new derivative term to be set
     */
    void update_d_term(float new_d);

    /**
     * @brief Updates the current PID term values
     *
     * @param new_p is the new proportional term to be set
     * @param new_i is the new integral term to be set
     * @param new_d is the new derivative term to be set
     */
    void update_pid_terms(float new_p, float new_i, float new_d);
    void update_pid_terms(pid_terms_t pid_terms_);
    pid_terms_t get_pid_terms();

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
     * @return PWM value (0-255) which correlates to the correction made
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
