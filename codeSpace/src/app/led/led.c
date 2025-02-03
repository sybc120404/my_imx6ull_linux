#include "led.h"

void led_init()
{
    gpio_pin_config_t config = {};

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10b0);

    config.direction = GPIO_DigitalOutput;
    config.outputLogic = 1;
    gpio_init(GPIO1, 3, &config);
}

/* led亮 */
void led_on()
{
    gpio_pinWrite(GPIO1, 3, 0);
}

/* led灭 */
void led_off()
{
    gpio_pinWrite(GPIO1, 3, 1);
}

void led_switch(LED_STATUS status)
{
    if(LED_ON == status)
    {
        led_on();
    }
    else
    {
        led_off();
    }
}