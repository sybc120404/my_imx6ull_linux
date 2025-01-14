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
    if(NULL == addr ||
        !(addr >= GPIO1_BASE && addr < (GPIO1_BASE + sizeof(GPIO_TYPE)) ||
        addr >= GPIO2_BASE && addr < (GPIO2_BASE + sizeof(GPIO_TYPE)) ||
        addr >= GPIO3_BASE && addr < (GPIO3_BASE + sizeof(GPIO_TYPE)) ||
        addr >= GPIO4_BASE && addr < (GPIO4_BASE + sizeof(GPIO_TYPE)) ||
        addr >= GPIO5_BASE && addr < (GPIO5_BASE + sizeof(GPIO_TYPE))))
    {
        printf("error addr\r\n");
        return -1;
    }

    *addr = value;

    return 0;
}