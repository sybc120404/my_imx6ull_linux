/**
 * @file    gpio.c
 * @brief   c file of gpio module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

/**
 * @brief Include files for the GPIO module.
 */

#include "gpio.h"

/**
 * @brief STATIC Function definition for the GPIO module.
 */

/**
 * @brief Function definition for the GPIO module.
 */

int gpio_reg_set_value(__IO uint32_t *addr, uint32_t value)
{
    if(NULL == addr)
    {
        return -1;
    }

    *addr = value;

    return 0;
}