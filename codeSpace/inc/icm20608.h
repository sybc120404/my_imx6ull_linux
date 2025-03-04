/*
    File:   icm20608.h
    Des:    c header of icm20608 module
    Date:   04Mar25
    Author: Cai
*/

#ifndef __ICM20608_H_
#define __ICM20608_H_

/*
    Include Files
*/

#include "6ull.h"
#include "debug.h"
#include "gpio.h"

/*
    Macro Definition
*/

/* 片选宏，选中时n=1，否则n=0，设置对应的GPIO */
#define IMC2068_CSN(n)  (n ? gpio_pinwrite(GPIO1, 20, 1) : gpio_pinwrite(GPIO1, 20, 0))

/*
    Function Declaration
*/

/* 初始化ICM20608外设 */
ERR_CODE icm20608_init();

#endif