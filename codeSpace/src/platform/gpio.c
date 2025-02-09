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

    gpio_interrupt_config_init(base, pin, config->interruptMode);
}

/* 使能指定IO中断 */
void gpio_interrupt_enable(GPIO_Type *base, unsigned int pin)
{
    if(NULL == base)
    {
        return;
    }

    base->IMR |= (1 << pin);
}

/* 关闭指定IO中断 */
void gpio_interrupt_disable(GPIO_Type *base, unsigned int pin)
{
    if(NULL == base)
    {
        return;
    }

    base->IMR &= ~(1 << pin);
}

/* 清除中断标志位 */
void gpio_clear_interrupt_flag(GPIO_Type *base, unsigned int pin)
{
    if(NULL == base)
    {
        return;
    }

    base->ISR |= (1 << pin);
}

/* GPIO中断初始化 */
void gpio_interrupt_config_init(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t mode)
{
    volatile uint32_t *icr = NULL;
    uint32_t icrShift = pin;

    if(NULL == base)
    {
        return;
    }

    base->EDGE_SEL &= ~(1 << pin);

    if(pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= 16;
    }

    switch(mode)
    {
        case gpio_int_low_level:
            *icr &= ~(3 << (2*icrShift));
            break;
        case gpio_int_high_level:
            *icr &= ~(3 << (2*icrShift));
            *icr |= (1 << (2*icrShift));
            break;
        case gpio_int_rising_edge:
            *icr &= ~(3 << (2*icrShift));
            *icr |= (2 << (2*icrShift));
            break;
        case gpio_int_falling_edge:
            *icr &= ~(3 << (2*icrShift));
            *icr |= (3 << (2*icrShift));
            break;
        case gpio_int_rising_or_falling_edge:
            base->EDGE_SEL |= (1 << pin);
            break;
        default:
            break; 
    }

}