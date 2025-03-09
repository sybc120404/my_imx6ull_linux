/*
    File:   ap3216c.h
    Des:    c header of ap3216c module
    Date:   23Feb25
    Author: Cai
*/

#ifndef __AP3216C_H_
#define __AP3216C_H_

/*
    Include files
*/

#include "i2c.h"

/*
    Macro Definition
*/

#define AP3216C_SYSTEM_CONF     (0x00)
#define AP3216C_INT_STATUS      (0x01)
#define AP3216C_INT_CLEAR       (0x02)
#define AP3216C_IR_DATA_LOW     (0x0A)
#define AP3216C_IR_DATA_HIGH    (0x0B)
#define AP3216C_ALS_DATA_LOW    (0x0C)
#define AP3216C_ALS_DATA_HIGH   (0x0D)
#define AP3216C_PS_DATA_LOW     (0x0E)
#define AP3216C_PS_DATA_HIGH    (0x0F)

#define AP3216C_ADDR      (0x1E)      // 从机地址

#define AP3216C_ALS_THRESHOLD_LOW   (128)   // 光照阈值

/*
    Type Definition
*/

typedef struct ap3216c_dev_struct
{
    uint16_t ir;    // 红外数据
    uint16_t ps;    // 距离数据
    uint16_t als;   // 光照数据
}AP3216C_DEV;

/*
    Data Declaration
*/

extern AP3216C_DEV ap3216c_dev;

/*
    Function Declaration
*/

/* AP3216C初始化 */
void ap3216c_init();

/* AP3216C读数据，1Byte */
ERR_CODE ap3216c_read_byte(uint8_t reg, OUT uint8_t *data);

/* AP3216C写数据，1Byte */
ERR_CODE ap3216c_write_byte(uint8_t reg, IN uint8_t data);

/* 读取ir ps als数据 */
ERR_CODE ap3216c_get_data();

#endif