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

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction; // direction
    uint8_t outputLogic;            // output val
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

#endif