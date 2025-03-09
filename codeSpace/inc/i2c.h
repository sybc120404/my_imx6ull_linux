/*
    File:   i2c.h
    Des:    c header of i2c module
    Date:   23Feb25
    Author: Cai
*/

#ifndef __I2C_H_
#define __I2C_H_

/*
    Include files
*/

#include "6ull.h"
#include "debug.h"

/*
    Typedef
*/

typedef enum _i2c_status
{
    I2C_STATUS_OK = 0,
    I2C_STATUS_BUSY,
    I2C_STATUS_IDLE,
    I2C_STATUS_NAK,
    I2C_STATUS_ARBITRATION_LOST,    // I2C总线仲裁丢失
    I2C_STATUS_TIMEOUT,
    I2C_STATUS_ADDRNAK,

    I2C_STATUS_ERROR
}I2C_STATUS;

typedef enum _i2c_direction
{
    I2C_WRITE = 0x0,    // 主机写
    I2C_READ = 0x1      // 主机读
}I2C_DIRECTION;

typedef struct _i2c_transfer
{
    unsigned char slaveAddress;      	/* 7位从机地址 */
    I2C_DIRECTION direction; 		    /* 传输方向 */
    unsigned int subaddress;       		/* 寄存器地址 */
    unsigned char subaddressSize;    	/* 寄存器地址长度 */
    unsigned char *volatile data;    	/* 数据缓冲区 */
    volatile unsigned int dataSize;  	/* 数据缓冲区长度 */
}I2C_TRANSFER;

/*
    Function Declaration
*/

/* I2C初始化 */
ERR_CODE i2c_init(I2C_Type *base);

/* start信号产生，从机地址，读写 */
I2C_STATUS i2c_starts(I2C_Type *base, uint8_t addr, I2C_DIRECTION direction);

/* stop信号产生 */
I2C_STATUS i2c_stop(I2C_Type *base);

/* restart信号 */
I2C_STATUS i2c_restart(I2C_Type *base, uint8_t addr, I2C_DIRECTION direction);

/* I2C状态检查 */
I2C_STATUS i2c_check_and_clear_error(I2C_Type *base, I2C_STATUS status);

/* 写数据 */
ERR_CODE i2c_write(I2C_Type *base, IN const uint8_t *data, uint32_t dataSize);

/* 读数据 */
ERR_CODE i2c_read(I2C_Type *base, OUT uint8_t *data, uint32_t dataSize);

/* I2C传输 */
I2C_STATUS i2c_transfer(I2C_Type *base, I2C_TRANSFER *xfer);

#endif