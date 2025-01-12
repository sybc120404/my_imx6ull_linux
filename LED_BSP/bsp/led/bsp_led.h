#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6u.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char LED_STATUS;

#define LED_OFF (0)
#define LED_ON  (1)

/* 初始化led */
void led_init();

/* led控制 */
void led_switch(LED_STATUS status);


#ifdef __cplusplus
}
#endif

#endif