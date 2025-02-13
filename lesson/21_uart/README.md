# UART

本例程讲串口，6ULL的串口可以用来实现多种功能，例如DMA，模块时钟。我们最常用的**收发数据**（TX_DATA(TXD) RX_DATA(RXD)）

STM32还有`USART`，多了同步的功能，硬件上体现为多一条时间线，一般它也可以仅用作UART的功能

## 串口协议简介

UART传输数据是按bit传输，发送和接收的分别使用一条线，至少需要三条线（发送、接收、地线）

![uart](https://github.com/sybc120404/image4md/blob/main/uart.png)

波特率：UART数据传输的速率，每秒传输的数据位数，一般选择9600 19200 115200

UART一般接口电平有TTL(高电平1，低电平0)和RS-232(-3~-15V逻辑1，+3~+15V逻辑0)

## 6ULL串口UART原理

开发板上用的是UART1

- UARTx_URXD寄存器存储串口接收到的数据
- UARTx_UTXD寄存器为发送数据寄存器
- UARTx_UCR1-4为串口控制寄存器
- UARTx_UFCR可以配置分频值。我们选择UART的时钟源是PLL3/6=480/6=80MHz，需要设置SCSDR寄存器来选择时钟源及分频值，经过这个分频，再经过UART_UFCR分频，得到最终频率
- UARTx_UFCR/UARTx_UBIR/UARTx_UBMR寄存器共同决定串口波特率

![BOUND](https://github.com/sybc120404/image4md/blob/main/BOUND.png)

以上寄存器的配置详见代码