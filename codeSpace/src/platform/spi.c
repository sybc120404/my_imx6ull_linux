/*
    File:   spi.c
    Des:    c file of SPI module
    Date:   4Mar25
    Author: Cai
*/

/*
    Include files
*/

#include "spi.h"

/*
    Note
*/
/*
    ECSPIx_CONREG寄存器：
    bits:
        31-20: 猝发数据长度，注意需要+1，比如0x0表示1bit
        19-18: 选择哪个SPI通道
        15-12: 时钟分频，0x0表示一分频
        11-8: 时钟分频，2^n分频
        7-4: 分别是SPI3-0通道的主从模式控制，0-slave, 1-master
        3: 1-数据写入TXFIFO时，立即启动SPI
        0: 0-disable SPI, 1-enable SPI

    ECSPIx_CONFIGREG寄存器
    bits:
        23-20: 分别是SPI3-0通道空闲时SCLK电平
        19-16: 分别是SPI3-0通道空闲时数据线电平
        15-12: 分别是SPI3-0通道的片选信号，0-低电平选中，1-高电平选中
        7-4: 分别是SPI3-0通道的CPOL
        3-0: 分别是SPI3-0通道的CPHA

    ECSPIx_PERIODREG寄存器
    bits:
        21-16: 片选信号延时
        15: 时钟源，0-SPI Clock, 1-32.768kHz
        14-0: 设置数据传输等待时间
    
    ECSPIx_STATREG寄存器
    bits:
        3: 0-RXFIFO为空，1-非空
        0: 1-TXFIFO为空，0-非空

    ECSPIx_TXDATA
    ECSPIx_RXDATA
*/

/*
    Function Definition
*/

/* SPI初始化 */
ERR_CODE spi_init(ECSPI_Type *base)
{
    if(NULL == base)
    {
        return ERR_BAD_PARAM;
    }

    base->CONREG = 0;
    base->CONREG = (1 << 0) | (1 << 3) | (0b0001 << 4) | (7 << 20);

    base->CONFIGREG = 0;

    base->PERIODREG = 0x2000;

    /* SPI时钟，ICM20608最高8MHz，这里不能超过 */
    // 来源是60MHz
    base->CONREG &= ~((0xf << 12) | (0xf << 8));    // 先清零
    base->CONREG |= (9 << 12);

    return ERR_NO_ERROR;
}

/* SPI发送/接收 */
/* SPI全双工，读写是一起的，读的时候也必须写一个无效数据 */
ERR_CODE spi_channel0_rw_byte(ECSPI_Type *base, uint8_t tx_data, uint8_t *rx_data)
{
    uint32_t rx = 0;
    uint32_t tx = tx_data;
    uint32_t cnt = 0xffffffff;

    if(NULL == base)
    {
        return ERR_BAD_PARAM;
    }
    
    /* 选择通道0 */
    base->CONREG &= ~(3 << 18);

    /* 发送数据 */
    while(0 == (base->STATREG & 1)) 
    {
        -- cnt;
        if(!cnt)
        {
            return ERR_SPI_TIMEOUT;
        }
    }
    base->TXDATA = tx;

    /* 数据接收 */
    cnt = 0xffffffff;
    while(0 == (base->STATREG & (1 << 3))) 
    {
        -- cnt;
        if(!cnt)
        {
            return ERR_SPI_TIMEOUT;
        }
    }
    rx = base->RXDATA;
    *rx_data = rx & 0xff;
    
    return ERR_NO_ERROR;
}