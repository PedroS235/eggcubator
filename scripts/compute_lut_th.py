import math

# Steinhart-Hart coefficients
STEINHART_A =0.001129148 
STEINHART_B =0.000234125 
STEINHART_C =0.0000000876741 
SERIES_RESISTOR = 10000  # 10K ohms
MAX_ADC_VALUE = 4095
KELVIN_TO_CELSIUS = 273.15

def resistance_from_adc(adc_value):
    """Calculate the resistance of the thermistor based on ADC value"""
    if adc_value <= 0:
        # Prevent division by zero or negative values
        return float('inf')  # Return an infinite resistance or handle separately
    return SERIES_RESISTOR * (MAX_ADC_VALUE / adc_value - 1)

def steinhart_hart_temperature_c(resistance):
    """Calculate the temperature in Celsius from the thermistor's resistance using Steinhart-Hart equation"""
    if resistance <= 0 or math.isinf(resistance):
        # Return a very high/low temperature if resistance is invalid
        return float('nan')  # You could also return a very high temperature like 1000°C or handle it in another way

    ln_resistance = math.log(resistance)
    inv_temp = STEINHART_A + STEINHART_B * ln_resistance + STEINHART_C * ln_resistance ** 3
    temperature_k = 1.0 / inv_temp  # Temperature in Kelvin
    temperature_c = temperature_k - KELVIN_TO_CELSIUS  # Convert to Celsius
    return temperature_c

# Generate the lookup table
lookup_table = []

for adc_value in range(1, MAX_ADC_VALUE + 1):  # Start from 1 to avoid division by zero
    resistance = resistance_from_adc(adc_value)
    temperature = steinhart_hart_temperature_c(resistance)
    lookup_table.append(temperature)

print(lookup_table)

# # Print or save the lookup table
# for adc_value, temp in enumerate(lookup_table):
#     print(f"ADC: {adc_value}, Temperature: {temp:.2f}°C")

