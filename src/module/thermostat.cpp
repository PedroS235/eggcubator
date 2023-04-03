/*
 * EggCubator - Arduino-based egg incubator controller
 * Copyright (C) 2023 Pedro Soares
 * See end of the file for extended copyright information
*/

#include "module/thermostat.h"
#include "configuration.h"
#include "pins.h"
Thermostat::Thermostat(unsigned long temp_reading_interval_, float temp_correction_)
	: temp(NAN)
	, last_temp_reading_time(0)
	, temp_target(0)
	, prev_temp_target(0)
{
	temp_sensor = new DHT(PIN_DHT, TYPE_DHT);
	temp_sensor->begin();
	pid = new PID(PID_TEMP_KP, PID_TEMP_KI, PID_TEMP_KD);

	temp_reading_interval = temp_reading_interval_;
	temp_correction = temp_correction_;
	pinMode(PIN_HEATER, OUTPUT);
}

void Thermostat::update_temp()
{
	unsigned long now = millis();
	if(now - last_temp_reading_time >= temp_reading_interval)
	{
		const float reading = temp_sensor->readTemperature();
		if(!isnan(reading))
		{
			temp = reading+temp_correction;
		}
		else
		{
			temp = NAN;
		}
		last_temp_reading_time = now;
	}
}

float Thermostat::get_temp()
{
	return temp;
}

void Thermostat::set_temp_correction(float new_correction)
{
	temp_correction = new_correction;
}

void Thermostat::set_temp_target(float new_target)
{
	temp_target = new_target;
}

void Thermostat::update_pid_p_term(float new_p)
{
	pid->update_p_term(new_p);
}

void Thermostat::update_pid_i_term(float new_i)
{
	pid->update_i_term(new_i);
}

void Thermostat::update_pid_d_term(float new_d)
{
	pid->update_d_term(new_d);
}

void Thermostat::update_pid_terms(float new_p, float new_i, float new_d)
{
	pid->update_pid_terms(new_p, new_i, new_d);
}

bool Thermostat::routine(float temp_target)
{
	update_temp();

	if(isnan(temp))
	{
		return false;
	}

	// Reset PID in case the temperature target changes
	if(prev_temp_target != temp_target)
	{
		pid->reset();
		prev_temp_target = temp_target;
	}
	float heater_pwm = pid->compute(temp_target, temp);

	// Control Heater power using PWM
	analogWrite(PIN_HEATER, heater_pwm);

	return true;
}

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
