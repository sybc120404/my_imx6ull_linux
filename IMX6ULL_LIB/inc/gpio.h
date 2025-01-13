/**
 * @file    gpio.h
 * @brief   c header file of gpio module.
 *
 * 
 * 
 * @author  Cai
 * @date    13Jan2025
 */

#ifndef __GPIO_H_
#define __GPIO_H_

/**
 * @brief Include files for the GPIO module.
 */

#include "common.h"

/**
 * @brief Typedefs for the GPIO module.
 */

typedef struct 
{
    __IO uint32_t DR;							
    __IO uint32_t GDIR; 							
    __IO uint32_t PSR;								
    __IO uint32_t ICR1; 							
    __IO uint32_t ICR2; 							 
    __IO uint32_t IMR;								 
    __IO uint32_t ISR;			
    __IO uint32_t EDGE_SEL;  
} GPIO_TYPE;


/**
 * @brief Macro definitions for the GPIO module.
 */

#define GPIO1				((GPIO_TYPE *)GPIO1_BASE)
#define GPIO2				((GPIO_TYPE *)GPIO2_BASE)
#define GPIO3				((GPIO_TYPE *)GPIO3_BASE)
#define GPIO4				((GPIO_TYPE *)GPIO4_BASE)
#define GPIO5				((GPIO_TYPE *)GPIO5_BASE)

#endif