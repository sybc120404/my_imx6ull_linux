#ifndef __LED_H
#define __LED_H

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "gpio.h"

typedef enum led_status
{
    LED_OFF = 0U,
    LED_ON = 1U,
}LED_STATUS;

void led_init();
void led_on();
void led_off();
void led_switch(LED_STATUS status);

#endif