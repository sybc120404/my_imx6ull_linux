/**
 * @file    delay.h
 * @brief   c header file of delay module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function declaration for the GPIO module.
 */

/**
 * @brief Short delay function.
 *
 * This function provides a short delay. The exact duration of the delay
 * depends on the value of the parameter `n`.
 *
 * @param n The number of iterations for the delay loop.
 */
void delay_short(volatile unsigned int n);

/**
 * @brief Delay function.
 *
 * This function provides a delay. When the main frequency is 396MHz,
 * one loop iteration approximately equals 1 millisecond.
 *
 * @param n The number of milliseconds to delay.
 */
void delay(volatile unsigned int n);

#ifdef __cplusplus
}
#endif

#endif