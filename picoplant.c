/**
 * @file picoplant.c
 * @author Harrison Gagnon
 * @brief Main file for the pico plant project 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "pico/stdio.h"
#include "arm.h"

int main()
{
    // Initialize arm chip
    arm_init();

    // Main loop
    while (true)
    {
        float temperature = read_onboard_temperature(TEMPERATURE_UNITS);
        printf("Onboard temperature = %.02f %c\n", temperature, TEMPERATURE_UNITS);
        sleep_ms(1000);
    }

    return 0;
}