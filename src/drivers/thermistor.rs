//! A module for reading temperature values from a thermistor.
//!
//! This module provides a `Thermistor` struct that facilitates the reading of temperature
//! values from a thermistor connected to an ADC channel on an ESP32 microcontroller.
//!
//! The thermistor's resistance is converted to a temperature value using the Steinhart-Hart
//! equation. The coefficients used in this equation are typical for a 10kΩ thermistor.

use std::borrow::Borrow;

use anyhow::Result;
use esp_idf_svc::{
    hal::{
        adc::{
            oneshot::{AdcChannelDriver, AdcDriver},
            Resolution,
        },
        gpio::ADCPin,
    },
    sys::{adc_bitwidth_t, EspError},
};

// TODO: Have different types of thermistors types and change config according.

const KELVIN_IN_CELCIUS: f32 = 273.15;

/// A struct representing a thermistor connected to an ADC channel.
///
/// The `Thermistor` struct provides methods to read the temperature from a thermistor
/// using the Steinhart-Hart equation to convert the thermistor's resistance to a temperature
/// value.
pub struct Thermistor<'d, T, M>
where
    T: ADCPin,
    M: Borrow<AdcDriver<'d, T::Adc>>,
{
    channel: AdcChannelDriver<'d, T, M>,
    pullup_res: u32,
}

impl<'d, T, M> Thermistor<'d, T, M>
where
    T: ADCPin,
    M: Borrow<AdcDriver<'d, T::Adc>>,
{
    /// Creates a new `Thermistor` instance.
    ///
    /// # Arguments
    ///
    /// * `channel` - The ADC channel driver for the thermistor.
    /// * `pullup_res` - The resistance value of the pull-up resistor in ohms.
    ///
    /// # Returns
    ///
    /// A new instance of `Thermistor`.
    pub fn new(channel: AdcChannelDriver<'d, T, M>, pullup_res: u32) -> Self {
        Self {
            channel,
            pullup_res,
        }
    }

    /// Reads the temperature from the thermistor.
    ///
    /// # Returns
    ///
    /// A `Result` containing the temperature in degrees Celsius if successful, or an `EspError` if
    /// an error occurred while reading from the ADC channel.
    pub fn read_temperature(&mut self) -> Result<f32, EspError> {
        // NOTE: Using the raw it's seems to be givin more accurate values.
        // The coefficients might need to be tweeked!
        let adc_value = self.channel.read_raw()?;
        let temperature = self.convert_to_temperature(adc_value);
        Ok(temperature)
    }

    /// Prints the temperature to the log.
    ///
    /// This method reads the temperature from the thermistor and logs the value using the `log` crate.
    /// If the temperature could not be read, it logs "NaN".
    pub fn print_temperature(&mut self) {
        match self.read_temperature() {
            Ok(temperature) => log::info!("Temperature: {:.2} °C", temperature),
            Err(_) => log::warn!("Temperature: NaN"),
        }
    }

    fn convert_to_temperature(&self, adc_value: u16) -> f32 {
        let resistance = self.adc_to_resistance(adc_value);
        self.resistance_to_temperature(resistance)
    }

    fn adc_to_resistance(&self, adc_value: u16) -> f32 {
        let max_adc_value = self.max_adc_value() as f32;
        let resistance = self.pullup_res as f32 * (max_adc_value / adc_value as f32 - 1.0);
        resistance
    }

    fn max_adc_value(&self) -> u32 {
        let resolution: adc_bitwidth_t = Resolution::default().into();
        2 << resolution - 1
    }

    fn resistance_to_temperature(&self, resistance: f32) -> f32 {
        let a = 0.001129148;
        let b = 0.000234125;
        let c = 0.0000000876741;

        let ln_resistance = resistance.ln();
        let temperature_kelvin = 1.0 / (a + b * ln_resistance + c * ln_resistance.powi(3));
        let temperature_celsius = temperature_kelvin - KELVIN_IN_CELCIUS;

        temperature_celsius
    }
}
