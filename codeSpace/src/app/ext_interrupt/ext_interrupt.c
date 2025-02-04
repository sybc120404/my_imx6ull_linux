/**
 * @file    ext_interrupt.c
 * @brief   c file of ext_interrupt module.
 *
 * 
 * 
 * @author  Cai
 * @date    04Feb2025
 */

/**
 * @brief Include files
 */

#include "ext_interrupt.h"
#include "gpio.h"
#include "delay.h"
#include "beep.h"

/**
 * @brief Static function definition
 */

static void gpio1_io18_irq_handler(unsigned int gicciar, void *param)
{
    static unsigned char state = 0;
    int pinState = 0;

    delay(10);  /* 实际上禁止中断服务函数中延时！！ */
    gpio_pinRead(GPIO1, 18, &pinState);
    if(0 == pinState)
    {
        state = !state;
        beep_switch(state);
    }

    /* 清除中断标志位 */
    gpio_clear_interrupt_flag(GPIO1, 18);

    return;
}

/**
 * @brief Function definition
 */

/* 初始化外部中断IO18_IO1 */
void ext_interrupt_init()
{
    gpio_pin_config_t config = {};
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
}
