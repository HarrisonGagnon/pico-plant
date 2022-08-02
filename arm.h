/**
 * @file arm.h
 * @author Harrison Gagnon
 * @brief This file is used to configure the RP2040 chip
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#ifndef _ARM_H
#define _ARM_H

// Pin Macros
#define LED_PIN PICO_DEFAULT_LED_PIN

// Define Temperature units
#define TEMPERATURE_UNITS 'F'

void arm_init()
{
    // Pin initialization
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Initialize adc for temp sensor 
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // Standard IO initialization
    stdio_init_all();
}

/* References for this implementation:
 * raspberry-pi-pico-c-sdk.pdf, Section '4.1.1. hardware_adc'
 * pico-examples/adc/adc_console/adc_console.c */
float read_onboard_temperature(const char unit) 
{
    /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
    const float conversionFactor = 3.3f / (1 << 12);

    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

    if (unit == 'C') 
    {
        return tempC;
    } 
    else if (unit == 'F') 
    {
        return tempC * 9 / 5 + 32;
    }

    return -1.0f;
}

#endif