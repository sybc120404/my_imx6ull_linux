/**
 * @file    beep.c
 * @brief   c file of beep module.
 *
 * 
 * 
 * @author  Cai
 * @date    19Jan2025
 */

/**
 * @brief Include files
 */

#include "beep.h"

/**
 * @brief Function Definition
 */

void beep_init()
{
    gpio_pin_config_t config = {};

    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10b0);
    
    config.direction = GPIO_DigitalOutput;
    config.outputLogic = 1;
    gpio_init(GPIO5, 1, &config);
}

void beep_on()
{
    gpio_pinWrite(GPIO5, 1, 0);
}

void beep_off()
{
    gpio_pinWrite(GPIO5, 1, 1);
}

void beep_switch(BEEP_STATUS status)
{
    if(BEEP_ON == status)
    {
        beep_on();
    }
    else if(BEEP_OFF == status)
    {
        beep_off();
    }

    return;
}