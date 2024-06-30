//! A module for implementing PID control and Bang-Bang control modes.
//!
//! This module provides a `PidControl` struct that allows for Proportional-Integral-Derivative (PID)
//! control as well as Bang-Bang control mode. The PID controller adjusts the control output based on
//! the error between the setpoint and the current value.

#[allow(dead_code)]
pub enum PidControlMode {
    AUTO,
    BANGBANG,
}

/// A struct representing a PID controller.
///
/// The `PidControl` struct provides methods to configure and compute control outputs based on the
/// PID algorithm or Bang-Bang control mode.
pub struct PidControl {
    kp: f32,
    ki: f32,
    kd: f32,
    min_out: f32,
    max_out: f32,
    min_integral: f32,
    max_integral: f32,
    integral_sum: f32,
    prev_error: f32,
    mode: PidControlMode,
}

/// Clamps a value between a minimum and maximum limit.
///
/// # Arguments
///
/// * `a` - The value to be clamped.
/// * `min` - The minimum limit.
/// * `max` - The maximum limit.
///
/// # Returns
///
/// The clamped value.
fn clamp(a: f32, min: f32, max: f32) -> f32 {
    if a > max {
        max
    } else if a < min {
        min
    } else {
        a
    }
}

#[allow(dead_code)]
impl PidControl {
    /// Creates a new `PidControl` instance.
    ///
    /// # Arguments
    ///
    /// * `kp` - Proportional gain.
    /// * `ki` - Integral gain.
    /// * `kd` - Derivative gain.
    /// * `min_out` - Minimum output limit.
    /// * `max_out` - Maximum output limit.
    /// * `min_integral` - Minimum integral limit.
    /// * `max_integral` - Maximum integral limit.
    /// * `mode` - Control mode (`AUTO` or `BANGBANG`).
    ///
    /// # Returns
    ///
    /// A new instance of `PidControl`.
    pub fn new(
        kp: f32,
        ki: f32,
        kd: f32,
        min_out: f32,
        max_out: f32,
        min_integral: f32,
        max_integral: f32,
        mode: PidControlMode,
    ) -> PidControl {
        PidControl {
            kp,
            ki,
            kd,
            min_out,
            max_out,
            min_integral,
            max_integral,
            integral_sum: 0.0,
            prev_error: 0.0,
            mode,
        }
    }

    /// Updates the PID gain terms.
    ///
    /// # Arguments
    ///
    /// * `kp` - New proportional gain.
    /// * `ki` - New integral gain.
    /// * `kd` - New derivative gain.
    pub fn update_terms(&mut self, kp: f32, ki: f32, kd: f32) {
        self.kp = kp;
        self.ki = ki;
        self.kd = kd;
    }

    /// Updates the output limits.
    ///
    /// # Arguments
    ///
    /// * `min` - New minimum output limit.
    /// * `max` - New maximum output limit.
    pub fn update_output_limits(&mut self, min: f32, max: f32) {
        self.min_out = min;
        self.max_out = max;
    }

    /// Updates the integral limits.
    ///
    /// # Arguments
    ///
    /// * `min` - New minimum integral limit.
    /// * `max` - New maximum integral limit.
    pub fn update_integral_limits(&mut self, min: f32, max: f32) {
        self.min_integral = min;
        self.max_integral = max;
    }

    /// Resets the PID controller's internal state.
    ///
    /// This method resets the integral sum and the previous error to zero.
    pub fn reset(&mut self) {
        self.prev_error = 0.0;
        self.integral_sum = 0.0;
    }

    /// Updates the control mode of the PID controller.
    ///
    /// # Arguments
    ///
    /// * `new_mode` - The new control mode (`AUTO` or `BANGBANG`).
    pub fn update_mode(&mut self, new_mode: PidControlMode) {
        self.mode = new_mode;
    }

    /// Computes the control output based on the setpoint and the current value.
    ///
    /// # Arguments
    ///
    /// * `setpoint` - The desired target value.
    /// * `curr_value` - The current value.
    ///
    /// # Returns
    ///
    /// The computed control output.
    pub fn compute(&mut self, setpoint: f32, curr_value: f32) -> f32 {
        let error = setpoint - curr_value;

        match self.mode {
            PidControlMode::AUTO => {
                let p = self.kp * error;
                let i = clamp(
                    self.ki * self.integral_sum,
                    self.min_integral,
                    self.max_integral,
                );
                let d = self.kd * (error - self.prev_error);

                self.integral_sum += error;
                self.prev_error = error;

                clamp(p + i + d, self.min_out, self.max_out)
            }

            PidControlMode::BANGBANG => {
                if error < 0.0 {
                    self.min_out
                } else {
                    self.max_out
                }
            }
        }
    }
}
