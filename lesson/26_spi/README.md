# SPI

SPI相比I2C的优势：

1. 速度快
2. 全双工通信

## SPI协议

SPI通信都是主机发起的，支持连接多个设备。标准SPI使用四根线进行通信

1. CS：选择与主机通信的从机，通信前将对应CS引脚拉低，进行选中
2. SCK：串行时钟。为SPI通信提供时钟
3. MOSI(Master Output Slave Input)：用于主机向从机发送数据
4. MISO(Master Input Slvae Output)：用于从机向主机发送数据

SPI有四种工作模式，通过串行时钟极性（CPOL）和相位（CPHA）的搭配来实现
CPOL=0表示串行时钟空闲时为低电平，CPOL=1表示高电平
CPHA=0表示串行时钟第一个跳变沿采集数据
CPHA=1表示串行时钟第二个跳变沿采集数据

![SPI](https://github.com/sybc120404/image4md/blob/main/SPI.png)

一般使用CPOL=0,CPHA=0的工作模式

## 6ULL SPI接口

1. 6ULL的SPI接口叫做ECSPI，支持全双工，主从可配置
2. 有四个硬件片选信号，可以使用软件片选，使一个SPI接口可以连接更多从机

## ICM20608

ALPHA开发板通过ECSPI3连接一个六轴传感器，引脚如下：

ECSPI3_SCLK:    UART2_RXD
ECSPI3_MOSI:    UART2_CTS
ECSPI3_SS0:     UART2_TXD
ECSPI3_MISO:    UART2_RTS

