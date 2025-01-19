#include "delay.h"
#include "beep.h"
#include "key.h"

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
    beep_init();

    while(1)
    {
        key_sta = key_get_status();
        if(key_sta == KEY_ON)
        {
            beep_on();
        }
        else
        {
            beep_off();
        }
    }

    return 0;
}