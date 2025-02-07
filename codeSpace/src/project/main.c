#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"
#include "ext_interrupt.h"
#include "epit.h"
#include "gpt.h"

int main(void)
{
    static LED_STATUS led = LED_OFF;

    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    led_init();
    beep_init();
    key_init();
    key_filter_init();
    gpt1_counter_init();

    while(1)
    {
        led = !led;
        led_switch(led);
        delay_ms(500);
    }

    return 0;
}