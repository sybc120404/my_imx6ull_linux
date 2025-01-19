#include "led.h"

void clk_enable()
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

void led_init()
{
    clk_enable();
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10b0);
    GPIO1->GDIR = 0x8;
    GPIO1->DR = 0x0;
}

/* led亮 */
void led_on()
{
    GPIO1->DR &= ~(1<<3);
}

/* led灭 */
void led_off()
{
    GPIO1->DR |= (1<<3);
}