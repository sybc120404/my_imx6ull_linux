/**
 * @file    epit.c
 * @brief   c file of epit module.
 *
 * 
 * 
 * @author  Cai
 * @date    05Feb2025
 */

/**
 * @brief Include files
 */

#include "epit.h"
#include "interrupt.h"
#include "led.h"

/**
 * @brief Static function definition
 */

/* 中断服务函数 */
static void epit1_handler(unsigned int gicciar, void *param)
{
    static uint8_t state = 0;

    state = !state;

    /*
        EPITx_SR寄存器，bit0=1说明中断发生，0表示未发生；寄存器设置1清零
    */
    if(1 == (EPIT1->SR & 0x1))
    {
        led_switch(state);
    }

    EPIT1->SR |= 0x1;

    return;
}

/**
 * @brief Function definition
 */

/* 初始化EPIT */
void epit1_init(uint32_t frac, uint32_t value)
{
    if(frac > 0xfff)
    {
        frac = 0xfff;
    }

    /*  
        EPITx_CR寄存器
        bits:
            31-26: Resvered
            25-24: 时钟源，00-不选择；01-外设时钟(ipg_clk)
            15-4：分频
            3：0-free running；1-set and forget
            2：0-禁止计数中断；1-使能计数中断
            1：0-起始计数值从上一次计数器被禁用时的计数开始；1-起始计数值从RL寄存器或0xffffffff开始（bit3控制）
            0：0-disable EPIT；1-enable EPIT
            其余bit可以初始化为0
     */
    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (frac << 4) | (0x1 << 24);

    /*
        EPITx_LR寄存器：设置计数起始值
    */
    EPIT1->LR = value;

    /*
        EPITx_CMPR寄存器：比较计数器，当LR寄存器值相等时，计时结束
    */
    EPIT1->CMPR = 0;

    /* 初始化中断 */
    GIC_EnableIRQ(EPIT1_IRQn);
    /* 注册中断服务函数 */
    sys_irq_handler_register(EPIT1_IRQn, epit1_handler, NULL);

    /* 开启定时器 */
    EPIT1->CR |= 0x1;

    return;
}