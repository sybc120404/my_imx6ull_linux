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
#include "rtc.h"
#include "ap3216c.h"

int main(void)
{
    LED_STATUS led = LED_OFF;
    uint16_t ir = 0;
    uint16_t ps = 0;
    uint16_t als = 0;
    
    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    uart1_init();

    DBG_ALZ_BRIEF("\r\nplatform init start...");
    
    rtc_init();

    DBG_ALZ_BRIEF("\r\napp init start...");

    led_init();
    beep_init();
    key_init();
    key_filter_init();
    gpt1_counter_init();
    
    ap3216c_init();     // 使用了精确delay，必须在gpt1后init

    DBG_ALZ_BRIEF("all init done.\r\n");

    while(1)
    {   
        ap3216c_read_data(&ir, &ps, &als);
        if(als <= 200)
        {
            printf("Sorround is tow dark, led on\r\n");
            led = LED_ON;
            led_switch(led);
        }
        else
        {
            led = !led;
            led_switch(led);
        }
        delay_ms(500);
    }

    return 0;
}

/* 解决链接libgcc.a问题 */
int raise()
{
    return 0;
}