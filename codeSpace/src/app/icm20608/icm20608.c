/*
    File:   icm20608.c
    Des:    c file of icm20608 module
    Date:   04Mar25
    Author: Cai
*/

/*
    Include Files
*/

#include "icm20608.h"
#include "delay.h"
#include "util.h"

/*
    Global Variables
*/

ICM20608_DEV icm20608_dev = {};

/*
    Function Definition
*/

/* 初始化ICM20608外设 */
ERR_CODE icm20608_init()
{
    gpio_pin_config_t cs_config = {};

    /* 1. SPI引脚初始化 */
    IOMUXC_SetPinMux(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0);  // 复用ECSPI3_SCLK
    IOMUXC_SetPinMux(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0);   // 复用为ECSPI3_MOSI
    IOMUXC_SetPinMux(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0);   // 复用为ECSPI3_MISO

    IOMUXC_SetPinConfig(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0x10b0); // 47k电阻,上拉
    IOMUXC_SetPinConfig(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0x10b0); 
    IOMUXC_SetPinConfig(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0x10b0);

    /* 
        片选引脚不使用硬件片选，只有4个，使用软件的
        使用了UART2_TX_DATA引脚作为片选，所以将其复用为普通IO
    */
    IOMUXC_SetPinMux(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0x10b0);
    // 设置方向为输出；默认低电平
    cs_config.direction = GPIO_DigitalOutput;
    cs_config.interruptMode = gpio_int_falling_edge;
    cs_config.outputLogic = 0;
    gpio_init(GPIO1, 20, &cs_config);

    /* 2. SPI控制器初始化 */
    PFM_IF_FAIL_RET(spi_init(ECSPI3));

    /* 3. ICM20608初始化 */

    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_PWR_MGMT_1, 0x80));		/* 复位，复位后为0x40,睡眠模式 */
	delay_ms(50);
	PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_PWR_MGMT_1, 0x01));		/* 关闭睡眠，自动选择时钟 */
	delay_ms(50);

    /* 测试读写接口 */
#if 1
    uint8_t who_am_i = 0;
    PFM_IF_FAIL_RET(icm20608_read_byte(ICM20_WHO_AM_I, &who_am_i));
    if(ICM20608D_ID == who_am_i || ICM20608G_ID == who_am_i)
    {
        DBG_ALZ_BRIEF("spi read successfully");
    }
    else
    {
        DBG_ERR("spi read failed");
        return ERR_SPI_READ_ERR;
    }
#endif

    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_SMPLRT_DIV, 0x00)); 	/* 输出速率是内部采样率	*/
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_GYRO_CONFIG, 0x18)); 	/* 陀螺仪±2000dps量程 */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_ACCEL_CONFIG, 0x18)); 	/* 加速度计±16G量程 */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_CONFIG, 0x04)); 		/* 陀螺仪低通滤波BW=20Hz */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_ACCEL_CONFIG2, 0x04)); 	/* 加速度计低通滤波BW=21.2Hz */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_PWR_MGMT_2, 0x00)); 	/* 打开加速度计和陀螺仪所有轴 */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_LP_MODE_CFG, 0x00)); 	/* 关闭低功耗 */
    PFM_IF_FAIL_RET(icm20608_write_byte(ICM20_FIFO_EN, 0x00));		/* 关闭FIFO	*/

#if 1
    uint8_t gyro_config = 0;
    PFM_IF_FAIL_RET(icm20608_read_byte(ICM20_GYRO_CONFIG, &gyro_config));
    if(0x18 == gyro_config)
    {
        DBG_ALZ_BRIEF("spi write successfully");
    }
    else
    {
        DBG_ERR("spi write failed");
        return ERR_SPI_WRITE_ERR;
    }
    #endif

    printf("icm20608 init done.\r\n");

    return ERR_NO_ERROR;
}

/* 从ICM20608读1byte数据 */
ERR_CODE icm20608_read_byte(uint8_t reg, OUT uint8_t *data)
{
    uint8_t rx_data = 0;
    if(NULL == data)
    {
        return ERR_BAD_PARAM;
    }

    reg |= 0x80;    // 读数据时，最高位为1

    ICM20608_CSN(0);    // 片选拉低，表示选中

    spi_channel0_rw_byte(ECSPI3, reg, &rx_data);    // 发送数据
    spi_channel0_rw_byte(ECSPI3, 0xff, &rx_data);   // 读数据，写一个无效值

    ICM20608_CSN(1);    // 片选拉高，表示取消选中

    *data = rx_data;

    return ERR_NO_ERROR;
}

/* 从ICM20608读多字节数据 */
ERR_CODE icm20608_read_n_byte(uint8_t reg, OUT uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    uint8_t tmp = 0;

    if(NULL == data)
    {
        return ERR_BAD_PARAM;
    }

    reg |= 0x80;

    spi_channel0_rw_byte(ECSPI3, reg, &tmp);    // 发送读取的寄存器地址

    ICM20608_CSN(0);
    
    for(i = 0; i < len; ++ i)
    {
        spi_channel0_rw_byte(ECSPI3, 0xff, data + i);   // 每次读地址会自增
    }

    ICM20608_CSN(1);

    return ERR_NO_ERROR;
}

/* 向ICM20608写1byte数据 */
ERR_CODE icm20608_write_byte(uint8_t reg, uint8_t data)
{
    uint8_t rx_data = 0;

    reg &= ~0x80;    // 写数据时，最高位为0

    ICM20608_CSN(0);    // 片选拉低，表示选中

    spi_channel0_rw_byte(ECSPI3, reg, &rx_data);    // 发送数据
    spi_channel0_rw_byte(ECSPI3, data, &rx_data);   // 写数据

    ICM20608_CSN(1);    // 片选拉高，表示取消选中

    return ERR_NO_ERROR;
}

/* 获取陀螺仪的分辨率 */
ERR_CODE icm20608_gyro_scale_get(float *gyro_scale)
{
	unsigned char data = 0;
	float gyroscale = 0;

    if(NULL == gyro_scale)
    {
        return ERR_BAD_PARAM;
    }
	
	PFM_IF_FAIL_RET(icm20608_read_byte(ICM20_GYRO_CONFIG, &data));
    data = (data >> 3) & 0X3;
	switch(data) {
		case 0: 
			gyroscale = 131;
			break;
		case 1:
			gyroscale = 65.5;
			break;
		case 2:
			gyroscale = 32.8;
			break;
		case 3:
			gyroscale = 16.4;
			break;
	}

    *gyro_scale = gyroscale;

	return ERR_NO_ERROR;
}

/* 获取加速度计的分辨率 */
ERR_CODE icm20608_accel_scale_get(uint16_t *accel_scale)
{
	uint8_t data;
	uint16_t accelscale;

    if(NULL == accel_scale)
    {
        return ERR_BAD_PARAM;
    }
	
	PFM_IF_FAIL_RET(icm20608_read_byte(ICM20_ACCEL_CONFIG, &data));
    data = (data >> 3) & 0X3;
	switch(data) {
		case 0: 
			accelscale = 16384;
			break;
		case 1:
			accelscale = 8192;
			break;
		case 2:
			accelscale = 4096;
			break;
		case 3:
			accelscale = 2048;
			break;
	}

    *accel_scale = accelscale;

	return ERR_NO_ERROR;
}

/* 获取ICM20608内部数据 */
ERR_CODE icm20608_get_data()
{
    uint8_t buffer[ICM20608_DATA_REG_NUM] = {};
    float gyro_scale = 0.0;
    uint16_t accel_scale = 0;

    PFM_IF_FAIL_RET(icm20608_read_n_byte(ICM20_ACCEL_XOUT_H, buffer, ICM20608_DATA_REG_NUM));

    PFM_IF_FAIL_RET(icm20608_gyro_scale_get(&gyro_scale));
    PFM_IF_FAIL_RET(icm20608_accel_scale_get(&accel_scale));

    /* 传感器原始数据 */
    icm20608_dev.accel_x_adc = (signed int)((buffer[0] << 8) | buffer[1]);
    icm20608_dev.accel_y_adc = (signed int)((buffer[2] << 8) | buffer[3]);
    icm20608_dev.accel_z_adc = (signed int)((buffer[4] << 8) | buffer[5]);
    icm20608_dev.temp_adc = (signed int)((buffer[6] << 8) | buffer[7]);
    icm20608_dev.gyro_x_adc = (signed int)((buffer[8] << 8) | buffer[9]);
    icm20608_dev.gyro_y_adc = (signed int)((buffer[10] << 8) | buffer[11]); 
    icm20608_dev.gyro_z_adc = (signed int)((buffer[12] << 8) | buffer[13]);

    /* 计算实际数据，扩大100倍以便计算浮点数 */
    icm20608_dev.gyro_x_act = ((float)(icm20608_dev.gyro_x_adc) / gyro_scale) * 100;
    icm20608_dev.gyro_y_act = ((float)(icm20608_dev.gyro_y_adc) / gyro_scale) * 100;
    icm20608_dev.gyro_z_act = ((float)(icm20608_dev.gyro_z_adc) / gyro_scale) * 100;
    icm20608_dev.accel_x_act = ((float)(icm20608_dev.accel_x_adc) / accel_scale) * 100;
    icm20608_dev.accel_y_act = ((float)(icm20608_dev.accel_y_adc) / accel_scale) * 100;
    icm20608_dev.accel_z_act = ((float)(icm20608_dev.accel_z_adc) / accel_scale) * 100;
    icm20608_dev.temp_act = (((float)(icm20608_dev.temp_adc) - 25 ) / 326.8 + 25) * 100;

    return ERR_NO_ERROR;
}

/* 打印设备真实数据 */
ERR_CODE icm20608_data_display()
{
    char dataStr[ICM20608_STR_LEN_MAX] = {};

    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.gyro_x_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("gyro_x: %s o/s\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.gyro_y_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("gyro_y: %s o/s\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.gyro_z_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("gyro_z: %s o/s\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.accel_x_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("accel_x: %s g\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.accel_y_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("accel_y: %s g\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.accel_z_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("accel_z: %s g\r\n", dataStr);
    PFM_IF_FAIL_RET(int_convert_float_str(icm20608_dev.temp_act, 2, dataStr, ICM20608_STR_LEN_MAX));
    printf("temp: %s ℃\r\n", dataStr);

    return ERR_NO_ERROR;
}