# DDR3

I.MX6U-ALPHA开发板带有256MB/512MB的DDR3内存芯片。一般Cortex-A芯片自带RAM很小，运行Linux的话完全不够，所以需要外接RAM芯片

## DDR内存简介

- RAM：随机存储器，可以随时读写，速度快，掉电丢失。SRAM/SDRAM/DDR都是RAM，一般用来保存程序数据，中间结果
- ROM：只读存储器，存储容量大，掉电数据不丢失，适合存储资料。Flash/EMMC/UFS/NAND Flash都是ROM

### SRAM

静态随机存储器，包含地址线、数据线、控制线

缺点是成本高，一般作为内部RAM或Cache使用

### SDRAM

同步动态随机存储器，需要时钟线，需要不断刷新保证数据不丢失

SDRAM成本相比SRAM低，容量大，但需要定时刷新，适合做高速缓存或MCU内部的RAM。

目前SDRAM已发展到第四代，分别为SDRAM, DDR SDRAM, DDR2 SDRAM, DDR3 SDRAM, DDR4 SDARM

### DDR

DDR是SDRAM的升级版本，大大提升了速度

DDR: DOuble Data Rate SDRAM

## DDR时间参数

1. 传输速率，表示最高传输速率
2. tRCD，行寻址到列寻址的延迟
3. CL参数，数据从存储单元到内存芯片的IO接口需要的时间
4. AL参数
5. tRC参数，表示两个ACTIVE命令，或者ACTIVE命令和REFRESH命令之间的周期
6. tRAS参数，ACTIVE命令到PRECHARGE命令之间的最小时间

## I.MX6U MMDC控制器

1. 对于I.MX6U，DDR的控制器为MMDC。多模支持DDR3/DDR3L LPDDR2，都是16bit
2. MMDC最高支持DDR3频率是400MHz，即800MT/s
3. MMDC提供DDR3连接信号，6ULL为DDR提供专用IO