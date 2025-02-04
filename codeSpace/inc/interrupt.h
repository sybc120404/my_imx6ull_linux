/**
 * @file    interrupt.h
 * @brief   c header file of interrupt module.
 *
 * 
 * 
 * @author  Cai
 * @date    04Feb2025
 */

#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "core_ca7.h"

/**
 * @brief Type definition
 */

/* 中断服务函数类型 */
typedef void (*system_irq_handler_t)(unsigned int gicciar, void *param);

/* 中断服务函数结构 */
typedef struct
{
    system_irq_handler_t irqHandler;
    void *userParam;
}sys_irq_handle_t;

/**
 * @brief Function declaration
 */

/* 中断初始化 */
void interrupt_init();

/* 注册中断处理函数 */
void sys_irq_handler_register(IRQn_Type irq, system_irq_handler_t handler, void *userParam);

/* 具体中断处理函数，IRQ_Handler会调用 */
void system_irqHandler(unsigned int gicciar);

#endif