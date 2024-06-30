mod core;
mod drivers;

use anyhow::Result;
use core::heater::Heater;
use drivers::thermistor::Thermistor;
use esp_idf_svc::hal::{
    adc::{
        attenuation::DB_11,
        oneshot::{config::AdcChannelConfig, AdcChannelDriver, AdcDriver},
        Resolution,
    },
    ledc::{config::TimerConfig, LedcDriver, LedcTimerDriver},
    peripherals::Peripherals,
    units::Hertz,
};
use std::thread;
use std::time::Duration;

fn main() -> Result<()> {
    esp_idf_svc::sys::link_patches();
    esp_idf_svc::log::EspLogger::initialize_default();

    // Take peripherals
    let peripherals = Peripherals::take().unwrap();

    // Creating the thermistor
    let thermistor_adc = AdcDriver::new(peripherals.adc1)?;
    let thermistor_adc_cfg = AdcChannelConfig {
        attenuation: DB_11,
        resolution: Resolution::default(),
        calibration: true,
    };
    let thermistor_channel =
        AdcChannelDriver::new(thermistor_adc, peripherals.pins.gpio7, &thermistor_adc_cfg)?;
    let thermistor = Thermistor::new(thermistor_channel, 10_000);

    // Creating Heater
    let heater_timer_config = TimerConfig {
        frequency: Hertz(100),
        resolution: esp_idf_svc::hal::ledc::Resolution::Bits12,
    };
    let heater_timer = LedcTimerDriver::new(peripherals.ledc.timer0, &heater_timer_config)?;
    let heater_pwm = LedcDriver::new(
        peripherals.ledc.channel0,
        heater_timer,
        peripherals.pins.gpio8,
    )?;
    let mut heater = Heater::new(thermistor, heater_pwm)?;

    // Small Test of the heater
    heater.heat(25.0);

    loop {
        thread::sleep(Duration::from_millis(500));
        heater.task();
    }
}
