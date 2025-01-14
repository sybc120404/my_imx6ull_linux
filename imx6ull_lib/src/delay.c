/**
 * @file    delay.c
 * @brief   c file of delay module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

/**
 * @brief Include files for the delay module.
 */

#include "delay.h"

/**
 * @brief Function definition for the GPIO module.
 */

void delay_short(volatile unsigned int n)
{
    while(n--){}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}