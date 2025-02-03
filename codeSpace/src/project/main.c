#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"

int main(void)
{
    //KEY_STATUS key_sta = KEY_OFF;

    clk_enable();
    imx6ull_clkInit();
    led_init();
    beep_init();
    key_init();

#if 0
    while(1)
    {
        key_sta = key_get_status();
        delay(10);
        key_sta = key_get_status();
        if(key_sta == KEY_ON)
        {
            led_on();
            beep_on();
        }
        else
        {
            led_off();
            beep_off();
        }
    }
#endif

    while(1)
    {
        led_on();
        delay(100);
        led_off();
        delay(100);
    }

    return 0;
}