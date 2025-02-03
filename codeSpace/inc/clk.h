/**
 * @file    clk.h
 * @brief   c header file of clk module.
 *
 * 
 * 
 * @author  Cai
 * @date    03Feb2025
 */

#ifndef __CLK_H_
#define __CLK_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"

/**
 * @brief Type definition
 */

/**
 * @brief Function declaration
 */

/* 使能外设时钟 */
void clk_enable();

/* 初始化时钟 */
void imx6ull_clkInit();

#endif