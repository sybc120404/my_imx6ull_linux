#include "delay.h"
#include "bsp_led.h"

int main(void)
{
    led_init();     /* 初始化led */

    while(1)
    {
        led_switch(LED_ON);   /* 点亮led */
        delay(2000); /* 延时2s */
        led_switch(LED_OFF);  /* 熄灭led */
        delay(500); /* 延时0.5s */
    }

    return 0;
}