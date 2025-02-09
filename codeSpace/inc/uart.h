/**
 * @file    uart.h
 * @brief   c header file of uart module.
 *
 * 
 * 
 * @author  Cai
 * @date    08Feb2025
 */

#ifndef __UART_H_
#define __UART_H_

/**
 * @brief Include files
 */

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"

/**
 * @brief Type definition
 */

/**
 * @brief Function declaration
 */

/* 初始化UART1，波特率115200 */
void uart1_init();

/* 打开UART */
void uart_enable(UART_Type *base);

/* 关闭UART */
void uart_disable(UART_Type *base);

/* UART复位 */
void uart_reset(UART_Type *base);

/* 发送字符串 */
void puts(char *str);

/* 发送1B数据 */
void putc(unsigned char data);

/* 接收1B数据 */
unsigned char getc();

#endif