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

int main(void)
{
    LED_STATUS led = LED_OFF;
    rtc_date_time dateTime = {};
    
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

    DBG_ALZ_BRIEF("all init done.\r\n");

    while(1)
    {   
        led = !led;
        led_switch(led);
        rtc_get_date_time(&dateTime);
        printf("%d-%d-%d %d:%d:%d\r\n", dateTime.year, dateTime.month, dateTime.day,
            dateTime.hour, dateTime.minute, dateTime.second);
        delay_ms(2000);
    }

    return 0;
}

/* 解决链接libgcc.a问题 */
int raise()
{
    return 0;
}