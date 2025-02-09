/**
 * @file    key_filter.c
 * @brief   c file of key_filter.
 *
 * 
 * 
 * @author  Cai
 * @date    06Feb2025
 */

/**
 * @brief Include files
 */

#include "key.h"
#include "core_ca7.h"
#include "interrupt.h"
#include "beep.h"
#include "epit.h"

/**
 * @brief Private Function definition
 */

/* 定时器中断处理函数 */
static void epit1_handler(unsigned int gicciar, void *param)
{
    static BEEP_STATUS status = BEEP_OFF;
    int gpioVal = 0;

    if(EPIT1->SR & 0x1)
    {
        /* 关闭定时器 */
        epit1_stop();

        /* 判断按键状态 */
        gpio_pinRead(GPIO1, 18, &gpioVal);
        if(0 == gpioVal)
        {
            status = !status;
            beep_switch(status);
        }
    }

    /* 清除中断标志位 */
    EPIT1->SR |= (1 << 0);
}

/* 初始化消抖定时器，参考epit1_init */
static void key_filter_epit1_init(uint32_t value)
{
    EPIT1->CR = 0;
    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (0x1 << 24);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    /* 初始化中断 */
    GIC_EnableIRQ(EPIT1_IRQn);
    /* 注册中断服务函数 */
    sys_irq_handler_register(EPIT1_IRQn, epit1_handler, NULL);
}

/* 中断服务函数 */
static void gpio1_io18_irq_handler(unsigned int gicciar, void *param)
{
    /* 开启定时器, 10ms */
    epit1_restart(66e6/100);

    /* 清除中断标志位 */
    gpio_clear_interrupt_flag(GPIO1, 18);
}

/**
 * @brief Function definition
 */

/* keyFilter初始化，参考ext_interrupt_init */
void key_filter_init()
{
    gpio_pin_config_t config = {};
    
    /* 按键初始化GPIO18_IO1 */
    // 设置复用
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    
    // 设置电气属性
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xf080);

    // 设置方向为输入；GPIO输入，无需设置电平
    config.direction = GPIO_DigitalInput;
    config.interruptMode = gpio_int_falling_edge;
    gpio_init(GPIO1, 18, &config);

    /* 使能中断ID */
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);

    /* 注册中断服务函数 */
    sys_irq_handler_register(GPIO1_Combined_16_31_IRQn, gpio1_io18_irq_handler, NULL);

    /* 使能中断 */
    gpio_interrupt_enable(GPIO1, 18);

    /* 初始化定时器 */
    key_filter_epit1_init(66e6/100);
}