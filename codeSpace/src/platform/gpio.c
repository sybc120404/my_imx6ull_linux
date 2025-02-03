/**
 * @file    gpio.c
 * @brief   c file of gpio module.
 *
 * 
 * 
 * @author  Cai
 * @date    03Feb2025
 */

/**
 * @brief Include files
 */
#include "gpio.h"

/**
 * @brief Function definition
 */

void gpio_pinWrite(GPIO_Type *base, int pin, int value)
{
    if(NULL == base)
    {
        return;
    }

    if(0 == value)
    {
        base->DR &= ~(1 << pin);
    }
    else
    {
        base->DR |= (1 << pin);
    }
}

void gpio_pinRead(GPIO_Type *base, int pin, int *value)
{
    if(NULL == base || NULL == value)
    {
        return;
    }

    *value = (((base->DR) >> pin) & 0x1);

    return;
}

void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config)
{
    if(NULL == base || NULL == config)
    {
        return;
    }

    /* direction */
    if(GPIO_DigitalInput == config->direction)
    {
        base->GDIR &= ~(1 << pin);
    }
    else
    {
        base->GDIR |= (1 << pin);
        /* set default output val */
        gpio_pinWrite(base, pin, config->outputLogic);
    }
}