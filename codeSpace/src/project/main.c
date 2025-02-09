#include "delay.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "clk.h"
#include "ext_interrupt.h"
#include "epit.h"
#include "gpt.h"
#include "uart.h"
#include "stdio.h"
#include "debug.h"

int main(void)
{
    int a = 0;
    int b = 0;

    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    uart1_init();

    DBG_ALZ_BRIEF("\r\napp init start...");

    led_init();
    beep_init();
    key_init();
    key_filter_init();
    gpt1_counter_init();

    DBG_ALZ_BRIEF("app init done.");

    while(1)
    {
        printf("Please enter two nums, split by blankspace: ");
        scanf("%d %d", &a, &b);
        printf("\r\n%d + %d = %d\r\n", a, b, a+b);
    }

    return 0;
}

/* 解决链接libgcc.a问题 */
int raise()
{
    return 0;
}