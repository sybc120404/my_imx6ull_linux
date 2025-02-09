/**
 * @file    uart.c
 * @brief   c file of uart module.
 *
 * 
 * 
 * @author  Cai
 * @date    08Feb2025
 */

/**
 * @brief Include files
 */

#include "uart.h"
#include "gpio.h"

/**
 * @brief Private Function
 */

static void uart_io_init()
{
    /* 设置IO复用 */
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);

    /* 设置电器属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10b0);
}

#if 1
/*
 * @description 		: 波特率计算公式，
 *    			  	  	  可以用此函数计算出指定串口对应的UFCR，
 * 				          UBIR和UBMR这三个寄存器的值
 * @param - base		: 要计算的串口。
 * @param - baudrate	: 要使用的波特率。
 * @param - srcclock_hz	:串口时钟源频率，单位Hz
 * @return		: 无
 */
static void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz)
{
    uint32_t numerator = 0u;		//分子
    uint32_t denominator = 0U;		//分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); //要先写UBIR寄存器，然后在写UBMR寄存器，3592页 
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}
#endif

/**
 * @brief Function definition
 */

/* 初始化UART1，波特率115200 */
void uart1_init()
{
    /* 初始化UART1的IO */
    uart_io_init();

    /* 配置UART1 */
    uart_disable(UART1);    /* 先关闭UART1 */
    uart_reset(UART1);

    /*
        UARTx_UCR2寄存器，配置奇偶校验等功能
        bits:
            14： 1-忽略UART的RST pin
            8： 0-关闭奇偶校验；1-开启奇偶校验
            7： 0-奇校验；1-偶校验
            6： 0-停止位为1bit；1-停止位为2bit
            5： 0-数据为7bit；1-数据为8bit
            2： 0-关闭发送；1-使能发送
            1： 0-关闭接收；1-使能接收
            0： 0-表示复位中；1-表示未在复位过程
    */
    UART1->UCR2 = 0;
    UART1->UCR2 = (1 << 1) | (1 << 2) | (1 << 5) | (0 << 6) | (0 << 8) | (1 << 14);

    /*
        UARTx_UCR3寄存器
        bits:
            2: 必须为1!!
    */
    UART1->UCR3 |= (1 << 2);

    /* 设置波特率，外设时钟在clk中设置 */
    /* UARTx_UFCR bit9-7控制分频：101-1分频 */
#if 0
    UART1->UFCR &= ~(7 << 7);   /* 清零 */
    UART1->UFCR |= (5 << 7);
    UART1->UBIR = 71;
    UART1->UBMR = 3124;
#else   /* 需要链接linux的数学库 */
    uart_setbaudrate(UART1, 115200, 80e6);
#endif

    /* 使能串口 */
    uart_enable(UART1);
}

/* 打开UART */
void uart_enable(UART_Type *base)
{
    if(NULL != base)
    {
        base->UCR1 |= (1 << 0);
    }
}

/* 关闭UART */
void uart_disable(UART_Type *base)
{
    if(NULL != base)
        base->UCR1 &= ~(1 << 0);
}

/* UART复位 */
void uart_reset(UART_Type *base)
{
    if(NULL != base)
    {
        base->UCR2 &= ~(1 << 0);    /* 清0 */
        while(0 == (base->UCR2  & 0x1));    /* 等待置为1 */
    }
}

/* 发送1B数据 */
void putc(unsigned char data)
{
    /* 
        UARTx_USR2寄存器
        bits:
            3： 1-传输完成；0-传输未完成
     */
    while(0 == ((UART1->USR2 >> 3) & 0x1));

    /* 发送即往UTXD寄存器写要发送的数据 */
    UART1->UTXD = data;
}

/* 接收1B数据 */
unsigned char getc()
{
    /* 
        UARTx_USR2寄存器
        bits:
            0： 1-有接收到数据；0-没有
     */
        while(0 == (UART1->USR2 & 0x1));    /* 等待数据 */
        /* UARTx_URXT的低8bit为数据 */
        return (UART1->URXD & 0xff);
}

/* 发送字符串 */
void puts(char *str)
{
    char *p = str;

    while(*p)
    {
        putc(*p);
        ++ p;
    }
}