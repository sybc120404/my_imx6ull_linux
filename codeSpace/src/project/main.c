#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"
#include "ext_interrupt.h"

int main(void)
{
    LED_STATUS led_status = LED_OFF;

    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    led_init();
    beep_init();
    key_init();
    ext_interrupt_init();

    while(1)
    {
        led_status = !led_status;
        led_switch(led_status);
        delay(500);
    }

    return 0;
}