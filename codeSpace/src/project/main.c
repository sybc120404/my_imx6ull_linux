#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"
#include "ext_interrupt.h"
#include "epit.h"

int main(void)
{
    LED_STATUS led = LED_OFF;

    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    led_init();
    beep_init();
    key_init();
    key_filter_init();

    while(1)
    {
        led = !led;
        led_switch(led);
        delay(500);
    }

    return 0;
}