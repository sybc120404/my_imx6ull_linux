# my_imx6ull_linux

记录I.MX6ULL_LINUX开发板使用

各工程构建目标产物命令：

LED_BSP: `make led`
BEEP: `make beep`
KEY: `make key`

## some notes

1. Makefile基本知识 - [Makefile](./notes/Makefile_note/)
2. NXP官方库函数 - [NXP_LIB](./notes/nxp_lib_note/)

## table of contents

1. LED汇编 - [LED_COMPILATION](./LED_COMPILATION/)
2. LED_C - [LED_C](./LED_C/)
3. LED-STM32规范版本 - [LED_STM32](./LED_STM32/)
4. LED-BSP工程管理，规范文件目录 - [LED_BSP](./LED_BSP/)
5. BEEP，蜂鸣器实验 - [BEEP](./BEEP/)
6. KEY，按键实验 - [KEY](./KEY/)

## 工程管理

(13Jan25)
1. 抽象出公用库，位于MY_LIB目录下
2. 每个例程的相关代码，放在单独一个文件目录下
3. `Makefile`文件仅在第一级目录下，根据需要生成每个例程的目标
4. DBG等库以静态库的方式加载

## 烧写bin文件

STM32需要烧写到内部FLASH
6ULL支持SD卡\EMMC\NAND\NOR\SPI FLASH启动，裸机例程选择烧写到SD卡中

1. 格式化U盘

![格式化](https://github.com/sybc120404/image4md/blob/main/RESET.png)

2. 烧写bin文件

对于I.MX，不能直接烧写bin文件，必须先添加头部信息，借住imxdownload软件实现

U盘连接到linux上，查看挂载的目录：拔插看一下增加的
```
ls /dev/sd* -l
```
![dev](https://github.com/sybc120404/image4md/blob/main/dev.png)

烧写命令
```
./imxdownload led.bin /dev/sdb(U盘的挂载目录)
```
![up](https://github.com/sybc120404/image4md/blob/main/up.png)

ixmdownload会向led.bin添加一个头部，生成新的load.imx文件，把它最终烧写到SD卡