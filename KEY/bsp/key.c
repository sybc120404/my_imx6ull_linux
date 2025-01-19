#include "key.h"

void key_init(void)
{
    // 设置复用
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    
    // 设置电气属性
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xf080);

    // 设置方向为输入
    GPIO1->GDIR &= ~(1 << 18);

    // GPIO输入，无需设置DR
}

KEY_STATUS key_get_status(void)
{
    static KEY_STATUS ret = KEY_OFF;

    if((GPIO1->DR & (1 << 18)) == 0)  // 低电平，表示按下
    {
        delay(10);  // 消抖
        if((GPIO1->DR & (1 << 18)) == 0)
        {
            ret = KEY_ON;
        }
    }
    else
    {
        ret = KEY_OFF;
    }

    return ret;
}