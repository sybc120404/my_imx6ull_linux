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

