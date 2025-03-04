/*
    File:   icm20608.c
    Des:    c file of icm20608 module
    Date:   04Mar25
    Author: Cai
*/

/*
    Include Files
*/

#include "icm20608.h"

/*
    Function Definition
*/

/* 初始化ICM20608外设 */
ERR_CODE icm20608_init()
{
    gpio_pin_config_t cs_config = {};

    /* 1. SPI引脚初始化 */
    IOMUXC_SetPinMux(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0);  // 复用ECSPI3_SCLK
    IOMUXC_SetPinMux(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0);   // 复用为ECSPI3_MOSI
    IOMUXC_SetPinMux(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0);   // 复用为ECSPI3_MISO

    IOMUXC_SetPinConfig(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0x10b0); // 47k电阻,上拉
    IOMUXC_SetPinConfig(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0x10b0); 
    IOMUXC_SetPinConfig(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0x10b0);

    /* 
        片选引脚不使用硬件片选，只有4个，使用软件的
        使用了UART2_TX_DATA引脚作为片选，所以将其复用为普通IO
    */
    IOMUXC_SetPinMux(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0x10b0);
    // 设置方向为输出；默认低电平
    cs_config.direction = GPIO_DigitalOutput;
    cs_config.interruptMode = gpio_int_falling_edge;
    cs_config.outputLogic = 0;
    gpio_init(GPIO1, 20, &cs_config);

    /* 2. SPI控制器初始化 */

    /* 3. ICM20608初始化 */
}
