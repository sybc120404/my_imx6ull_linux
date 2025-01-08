#include "led.h"

/* 使能gpio时钟 */
void clk_enable()
{
    CCGR2 = 0xffffffff;
}

/* 初始化led */
void led_init()
{
    SW_MUX_GPIO1_IO03 = 0x5;        /* 复用为GPIO1_IO03 */
    SW_PAD_GPIO1_IO03 = 0x10b0;     /* 设置电气属性 */
    GPIO1_GDIR = 0x8;               /* 设置为输出 */
    GPIO1_DR = 0x0;                 /* 打开led灯 */
}

/* 短延时 */
void delay_short(volatile unsigned int n)
{
    while(n--){}
}

/* 延时，主频396MHz时，一次循环大概1ms */
void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

/* led亮 */
void led_on()
{
    GPIO1_DR &= ~(1<<3);
}

/* led灭 */
void led_off()
{
    GPIO1_DR |= (1<<3);
}

int main()
{
    /* 初始化led */
    clk_enable();
    led_init();

    /* 设置led闪烁 */
    while(1)
    {
        led_on();
        delay(500);
        led_off();
        delay(500);
    }

    return 0;
}