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
#include "icm20608.h"

/*
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);

    printf("FPU and NEON init done.\r\n");
}

void foxi_init()
{
    printf("========================================\r\n");
    DBG_ALZ_BRIEF("init start...\r\n");
    printf("========================================\r\n");
}

int main(void)
{
    LED_STATUS led = LED_OFF;
    
    interrupt_init();
    clk_enable();
    imx6ull_clkInit();
    uart1_init();

    foxi_init();

    DBG_ALZ_BRIEF("\r\nplatform init start...");
    
    imx6ul_hardfpu_enable();
    rtc_init();

    DBG_ALZ_BRIEF("\r\napp init start...");

    led_init();
    beep_init();
    key_init();
    key_filter_init();
    gpt1_counter_init();
    
    ap3216c_init();     // 使用了精确delay，必须在gpt1后init
    icm20608_init();

    printf("========================================\r\n");
    DBG_ALZ_BRIEF("all init done.\r\n");
    printf("========================================\r\n");

    while(1)
    {   
        ap3216c_get_data();
        if(AP3216C_ALS_THRESHOLD_LOW >= ap3216c_dev.als)
        {
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