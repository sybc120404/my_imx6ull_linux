#ifndef __LED_H
#define __LED_H

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "gpio.h"

void led_init();
void led_on();
void led_off();

#endif