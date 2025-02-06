/**
 * @file    epit.h
 * @brief   c header file of epit module.
 *
 * 
 * 
 * @author  Cai
 * @date    05Feb2025
 */

#ifndef __EPIT_H_
#define __EPIT_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "core_ca7.h"

/**
 * @brief Function declaration
 */

/* 初始化EPIT */
void epit1_init(uint32_t frac, uint32_t value);

/* 关闭EPIT1定时器 */
void epit1_stop();

/* 重启EPIT1定时器 */
void epit1_restart(uint32_t value);

#endif