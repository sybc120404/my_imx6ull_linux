#include "bsp_led.h"

LED_STATUS led_status = LED_OFF;

/* led亮 */
static void led_on()
{
    GPIO1->DR &= ~(1<<3);
    led_status = LED_ON;
}

/* led灭 */
static void led_off()
{
    GPIO1->DR |= (1<<3);
    led_status = LED_OFF;
}

/* 初始化led */
void led_init()
{
    ccm_reg_set_value(&(CCM->CCGR2), 0xffffffff);                       /* 使能GPIO1时钟 */
    iomux_mux_reg_set_value(&(IOMUX_SW_MUX->GPIO1_IO03), 0x5);         /* 复用为GPIO1_IO03 */
    iomux_mux_reg_set_value(&(IOMUX_SW_PAD->GPIO1_IO03), 0x10b0);      /* 设置电气属性 */
    gpio_reg_set_value(&(GPIO1->GDIR), 0x8);    /* 设置为输出 */
    led_on();
}

/* led控制 */
void led_switch(LED_STATUS status)
{
    if(status == LED_OFF && led_status == LED_ON)
    {
        led_off();
    }
    else if(status == LED_ON && led_status == LED_OFF)
    {
        led_on();
    }
}