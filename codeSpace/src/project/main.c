#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"
#include "ext_interrupt.h"
#include "epit.h"

int main(void)
{
    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    led_init();
    beep_init();
    key_init();
    ext_interrupt_init();
    epit1_init(0, 66e6/2);

    while(1)
    {
        delay(500);
    }

    return 0;
}