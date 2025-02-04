/**
 * @file    interrupt.c
 * @brief   c file of interrupt module.
 *
 * 
 * 
 * @author  Cai
 * @date    04Feb2025
 */

/**
 * @brief Include files
 */

#include "interrupt.h"

/**
 * @brief Global data
 */

/* 中断处理函数表 */
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS] = {};
/* 中断嵌套数量 */
static unsigned int irqNestNum = 0;

/**
 * @brief Private function definition
 */

/* 默认中断服务函数 */
static void default_irqHandler(unsigned int gicciar, void *userParam)
{
    return;
}

static void sys_irq_table_init()
{
    unsigned int  i = 0;
    for(i = 0; i < NUMBER_OF_INT_VECTORS; ++ i)
    {
        irqTable[i].irqHandler = default_irqHandler;
        irqTable[i].userParam = NULL;
    }

    return;
}

/**
 * @brief Function definition
 */

/* 中断初始化 */
void interrupt_init()
{
    GIC_Init();
    sys_irq_table_init();

    irqNestNum = 0;

    return;
}

/* 注册中断处理函数 */
void sys_irq_handler_register(IRQn_Type irq, system_irq_handler_t handler, void *userParam)
{
    if(irq >= NUMBER_OF_INT_VECTORS || NULL == handler)
    {
        return;
    }

    irqTable[irq].irqHandler = handler;
    irqTable[irq].userParam = userParam;

    return;
}

/* 具体中断处理函数，IRQ_Handler会调用 */
void system_irqHandler(unsigned int gicciar)
{
    if(gicciar >= NUMBER_OF_INT_VECTORS)
    {
        return;
    }

    ++ irqNestNum;

    irqTable[gicciar].irqHandler(gicciar, irqTable[gicciar].userParam);

    -- irqNestNum;

    return;
}