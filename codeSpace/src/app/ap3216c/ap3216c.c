/*
    File:   ap3216c.c
    Des:    c file of ap3216c module
    Date:   23Feb25
    Author: Cai
*/

/*
    Include Files
*/

#include "ap3216c.h"
#include "gpio.h"
#include "delay.h"
#include "stdio.h"

/*
    Gloabl Variables
*/

AP3216C_DEV ap3216c_dev = {};

/*
    Function Declaration
*/

/* AP3216C初始化 */
void ap3216c_init()
{
    uint8_t value = 0;
    /* IO初始化 */
    IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL, 1);   // 复用为I2C1_SCL，参数1表示允许GPIO引脚配置为输出时，依然可以读取电平状态
    IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA, 1);   // 复用为I2C1_SDA
    IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL, 0x70b0); // 47k电阻,上拉
    IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA, 0x70b0); 

    /* I2C接口初始化 */
    i2c_init(I2C1);

    /* AP3216C初始化 */
    ap3216c_write_byte(AP3216C_SYSTEM_CONF, 0x4);    // reset
    delay_ms(50);
    ap3216c_write_byte(AP3216C_SYSTEM_CONF, 0x3);    // 设置ALS+PS+IR模式
    ap3216c_read_byte(AP3216C_SYSTEM_CONF, &value);

    printf("ap3216c init done.\r\n");
}

/* AP3216C读数据，1Byte */
ERR_CODE ap3216c_read_byte(uint8_t reg, OUT uint8_t *data)
{
    I2C_STATUS status = 0;
    uint8_t value = 0;
    I2C_TRANSFER transfer = {};

    if(NULL == data)
    {
        return ERR_BAD_PARAM;
    }

    transfer.slaveAddress = AP3216C_ADDR;
    transfer.direction = I2C_READ;
    transfer.subaddress = reg;
    transfer.subaddressSize = 1;
    transfer.data = &value;
    transfer.dataSize = 1;

    status = i2c_transfer(I2C1, &transfer);
    if(I2C_STATUS_OK == status)
    {
        *data = *(transfer.data);
    }
    else
    {
        return ERR_I2C_ERR;
    }

    return ERR_NO_ERROR;
}

/* AP3216C写数据，1Byte */
ERR_CODE ap3216c_write_byte(uint8_t reg, IN uint8_t data)
{
    I2C_STATUS status = 0;
    I2C_TRANSFER transfer = {};

    transfer.slaveAddress = AP3216C_ADDR;
    transfer.direction = I2C_WRITE;
    transfer.subaddress = reg;
    transfer.subaddressSize = 1;
    transfer.data = &data;
    transfer.dataSize = 1;

    status = i2c_transfer(I2C1, &transfer);

    return status == I2C_STATUS_OK ? ERR_NO_ERROR : ERR_I2C_ERR;
}

/* 读取ir ps als数据 */
ERR_CODE ap3216c_get_data()
{
    uint8_t buf[6] = {};
    uint8_t i = 0;
    ERR_CODE errCode = 0;

    for(i = 0; i < 6; ++i)
    {
        errCode = ap3216c_read_byte(AP3216C_IR_DATA_LOW+i, buf+i);
        if(ERR_NO_ERROR != errCode)
            DBG_ERR("ap3216c read data %d err %d", i, errCode);
    }

    if(buf[0] & 0x80)       // IR和PS数据无效
    {
        ap3216c_dev.ir = 0;
        ap3216c_dev.ps = 0;
    }
    else
    {
        ap3216c_dev.ir = ((uint16_t)buf[1] << 2) | (buf[0] & 0x03);
        ap3216c_dev.ps = (((uint16_t)buf[5] & 0x3f) << 4) | (buf[4] & 0x0f);
    }

    ap3216c_dev.als = ((uint16_t)buf[3] << 8) | (buf[2]);

    return errCode;
}