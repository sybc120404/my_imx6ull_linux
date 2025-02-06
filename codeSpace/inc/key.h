#ifndef __KEY_H
#define __KEY_H

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "delay.h"
#include "gpio.h"

typedef enum
{
    KEY_ON = 0,
    KEY_OFF
}KEY_STATUS;

/*
    Function Declaration
*/

void key_init(void);

KEY_STATUS key_get_status(void);

/* KEY_FILTER */

/* keyFilter初始化 */
void key_filter_init();

#endif