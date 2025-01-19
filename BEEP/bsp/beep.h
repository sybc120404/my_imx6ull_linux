/**
 * @file    beep.h
 * @brief   c header file of beep module.
 *
 * 
 * 
 * @author  Cai
 * @date    19Jan2025
 */

#ifndef __BEEP_H
#define __BEEP_H

/**
 * @brief Include files
 */
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "delay.h"

void beep_init();

void beep_on();

void beep_off();

#endif