/**
 * @file    gpt.c
 * @brief   c file of gpt module.
 *
 * 
 * 
 * @author  Cai
 * @date    07Feb2025
 */

/**
 * @brief Include files
 */

#include "gpt.h"
#include "led.h"

/**
 * @brief Private definition
 */

static void gpt1_handler(unsigned int gicciar, void *param)
{
    static LED_STATUS led = LED_OFF;

    if(GPT1->SR & 0x1)
    {
        led = !led;
        led_switch(led);
    }

    GPT1->SR |= 1;  /* 清除中断标志位 */
}

/**
 * @brief Function definition
 */

/* GPT1用作定时器时的初始化 */
void gpt1_timer_init()
{
    /*
        GPTRx_CR寄存器，用于配置GPT各项属性
        bits
            15: 软件复位标志，0-未处于复位状态，1-处于复位状态。该位自动变化
            9： 定时器运行模式，0-restart模式，1-free-run
            8-6:    控制时钟源，000-No Clock, 001-ipg_clk, 其余省略
            1： 控制定时器重启时的计数值，0-从上次结束的计数值开始，1-从0开始
            0:  0-关闭GPT定时器；1-使能定时器
    */
    GPT1->CR = 0;   /* 清除GPT状态 */

    GPT1->CR = 1 << 15;                 /* 设置软复位标志位1 */
    while((GPT1->CR >> 15) & 0x1){}     /* 等待复位结束 */

    GPT1->CR = (1 << 1) | (0x1 << 6) | (0 << 9);

    /*
        GPTx_PR寄存器，控制分频
        bits:
            11-0:   分频值，0x0表示1分频
    */
    GPT1->PR = 65;   /* 66分频 */

    /*
        GPTx_OCR1寄存器，控制输出比较通道1的比较值
        bits:
            31-0：  比较值
    */
    GPT1->OCR[0] = 1e6/2;   /* 中断周期500ms */

    /*
        GPTx_IR寄存器，控制输出比较通道的中断
        bits:
            0:  输出比较通道1的中断，0-disable，1-enable
    */
    GPT1->IR = 1 << 0;      /* 开启输出比较通道1中断 */

    GIC_EnableIRQ(GPT1_IRQn);        /* 开启中断号 */

    sys_irq_handler_register(GPT1_IRQn, gpt1_handler, NULL); /* 注册中断服务函数 */

    GPT1->CR |= 1;  /* 开启定时器 */
}

/* GPT1用于计数器时的初始化 */
void gpt1_counter_init()
{
    /*
        GPTRx_CR寄存器，用于配置GPT各项属性
        bits
            15: 软件复位标志，0-未处于复位状态，1-处于复位状态。该位自动变化
            9： 定时器运行模式，0-restart模式，1-free-run
            8-6:    控制时钟源，000-No Clock, 001-ipg_clk, 其余省略
            1： 控制定时器重启时的计数值，0-从上次结束的计数值开始，1-从0开始
            0:  0-关闭GPT定时器；1-使能定时器
    */
    GPT1->CR = 0;   /* 清除GPT状态 */

    GPT1->CR = 1 << 15;                 /* 设置软复位标志位1 */
    while((GPT1->CR >> 15) & 0x1){}     /* 等待复位结束 */

    GPT1->CR = (1 << 1) | (0x1 << 6) | (0 << 9);

    /*
        GPTx_PR寄存器，控制分频
        bits:
            11-0:   分频值，0x0表示1分频
    */
    GPT1->PR = 65;   /* 66分频 */

    /* 以上配置和gpt1_timer_init一致 */

    GPT1->CR |= 1;  /* 开启定时器 */
}