/**
 * @file    gpt.h
 * @brief   c header file of gpt module.
 *
 * 
 * 
 * @author  Cai
 * @date    07Feb2025
 */

#ifndef __GPT_H_
#define __GPT_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "interrupt.h"

/**
 * @brief Type definition
 */

/**
 * @brief Function declaration
 */

/* GPT1用作定时器时的初始化 */
void gpt1_timer_init();

/* GPT1用于计数器时的初始化 */
void gpt1_counter_init();

#endif