#ifndef __KEY_H
#define __KEY_H

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "delay.h"

typedef enum
{
    KEY_ON = 0,
    KEY_OFF
}KEY_STATUS;

void key_init(void);

KEY_STATUS key_get_status(void);

#endif