/**
 * @brief Include files
 */

#include "key.h"

void key_init(void)
{
    gpio_pin_config_t config = {};
    // 设置复用
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    
    // 设置电气属性
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xf080);

    // 设置方向为输入；GPIO输入，无需设置电平
    config.direction = GPIO_DigitalInput;
    gpio_init(GPIO1, 18, &config);
}

KEY_STATUS key_get_status(void)
{
    KEY_STATUS ret = KEY_OFF;
    int key_gpio_val = 0;

    gpio_pinRead(GPIO1, 18, &key_gpio_val);
    if(key_gpio_val == 0)  // 低电平，表示按下
    {
        delay(10);  // 消抖
        gpio_pinRead(GPIO1, 18, &key_gpio_val);
        if(key_gpio_val == 0)
        {
            ret = KEY_ON;
        }
    }

    return ret;
}