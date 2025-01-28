#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"

static void clk_enable()
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

int main(void)
{
    KEY_STATUS key_sta = KEY_OFF;

    clk_enable();
    led_init();
    beep_init();
    key_init();

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

    return 0;
}