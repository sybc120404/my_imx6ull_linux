/**
 * @file    gpio.h
 * @brief   c header file of gpio module.
 *
 * 
 * 
 * @author  Cai
 * @date    03Feb2025
 */

#ifndef __GPIO_H_
#define __GPIO_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"

/**
 * @brief Type definition
 */

typedef enum _gpio_pin_direction
{
    GPIO_DigitalInput = 0U,
    GPIO_DigitalOutput = 1U,
}gpio_pin_direction_t;

/* 中断触发类型 */
typedef enum
{
    gpio_no_int_mode = 0U,  /* 无触发 */
    gpio_int_low_level = 1U,
    gpio_int_high_level = 2U,
    gpio_int_rising_edge = 3U,
    gpio_int_falling_edge = 4U,
    gpio_int_rising_or_falling_edge = 5U,
}gpio_interrupt_mode_t;

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction; // direction
    uint8_t outputLogic;            // output val
    gpio_interrupt_mode_t interruptMode;    /* 中断方式 */
}gpio_pin_config_t;

/**
 * @brief Function declaration
 */

/* 设置GPIO高低电平 */
void gpio_pinWrite(GPIO_Type *base, int pin, int value);

/* 读GPIO高低电平 */
void gpio_pinRead(GPIO_Type *base, int pin, int *value);

/* GPIO初始化 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);

/* 使能指定IO中断 */
void gpio_interrupt_enable(GPIO_Type *base, unsigned int pin);

/* 关闭指定IO中断 */
void gpio_interrupt_disable(GPIO_Type *base, unsigned int pin);

/* 清除中断标志位 */
void gpio_clear_interrupt_flag(GPIO_Type *base, unsigned int pin);

/* GPIO中断初始化 */
void gpio_interrupt_config_init(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t mode);

#endif