#ifndef __LED_SDK_H
#define __LED_SDK_H

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "delay.h"

void clk_enable();
void led_init();
void led_on();
void led_off();

#endif