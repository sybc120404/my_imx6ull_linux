/**
 * @file    beep.c
 * @brief   c file of beep module.
 *
 * 
 * 
 * @author  Cai
 * @date    19Jan2025
 */

/**
 * @brief Include files
 */

#include "beep.h"

void beep_init()
{
    // gpio5_clk无需初始化
    
    // IO复用为GPIO
    iomux_mux_reg_set_value(&(IOMUX_SW_PAD->SNVS_TAMPER1), 0x5);

    // 
}