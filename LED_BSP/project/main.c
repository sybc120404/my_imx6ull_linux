#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"

int main(void)
{
    clk_enable();   /* 使能GPIO1时钟 */
    led_init();     /* 初始化led */

    while(1)
    {
        led_switch(LED_ON);   /* 点亮led */
        delay(500); /* 延时500ms */
        led_switch(LED_OFF);  /* 熄灭led */
        delay(500); /* 延时500ms */
    }

    return 0;
}