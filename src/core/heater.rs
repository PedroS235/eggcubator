use super::super::drivers::thermistor::Thermistor;
use super::pid_control::{self, PidControl};
use anyhow::Result;
use esp_idf_svc::hal::adc::oneshot::AdcDriver;
use esp_idf_svc::hal::gpio::ADCPin;
use esp_idf_svc::hal::{
    gpio::{OutputMode, Pin, PinDriver},
    ledc::LedcDriver,
};
use log::info;
use std::borrow::Borrow;

pub struct Heater<'d, T, A>
where
    T: ADCPin,
    A: Borrow<AdcDriver<'d, <T as ADCPin>::Adc>>,
{
    pid: PidControl,
    thermistor: Thermistor<'d, T, A>,
    pwm: LedcDriver<'d>,
    target_temperature: f32,
}

impl<'d, T, A> Heater<'d, T, A>
where
    T: ADCPin,
    A: Borrow<AdcDriver<'d, <T as ADCPin>::Adc>>,
{
    pub fn new(thermistor: Thermistor<'d, T, A>, pwm_driver: LedcDriver<'d>) -> Result<Self> {
        // TODO: When configuration is ready, take the value from config.
        // For now these are some generics
        let control = PidControl::new(
            0.5,
            0.2,
            0.1,
            0.0,
            255.0,
            0.0,
            100.0,
            pid_control::PidControlMode::AUTO,
        );

        Ok(Self {
            pid: control,
            thermistor,
            pwm: pwm_driver,
            target_temperature: 0.0,
        })
    }

    pub fn heat(&mut self, target: f32) {
        self.target_temperature = target;
    }

    pub fn task(&mut self) {
        let current_temperature = self.thermistor.read_temperature().unwrap();
        let pwm_value = self
            .pid
            .compute(self.target_temperature, current_temperature) as u32;
        info!(
            "Current temp: {} | Output: {}",
            current_temperature, pwm_value
        );
        self.pwm.set_duty(pwm_value).unwrap();
    }
}
