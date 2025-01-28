#include "led.h"

void led_init()
{
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