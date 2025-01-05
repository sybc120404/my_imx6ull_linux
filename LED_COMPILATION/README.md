# LED_COMPILATION

记录汇编LED实验

## 汇编LED原理分析

### 为什么需要Cortex-A汇编

1. 需要汇编初始化一些SOC（system on chip）外设
2. 使用汇编初始化DDR(I.MX6ULL不需要)
3. 设置SP指针（**堆栈指针**），一般指向DDR，**设置好C语言运行环境**

> DDR 是 "Double Data Rate" 的缩写，指的是一种内存技术。DDR 内存可以在一个时钟周期内传输两次数据（一次在时钟信号的上升沿，一次在下降沿），因此比传统的单数据速率 (SDR) 内存速度更快。
> 在嵌入式系统中，初始化 DDR 内存通常是启动过程中的一个关键步骤，因为它涉及到设置内存控制器的各种参数，以确保内存能够正确工作。这些参数可能包括时序设置、刷新率、驱动强度等。

### Cortex-A LED 原理

![LED底板原理图](https://github.com/sybc120404/image4md/blob/main/led.png)

可以看出LED0低电平时，led灯亮，否则灭

![LED0 GPIO对应](https://github.com/sybc120404/image4md/blob/main/led0_gpio.png)

再看CORE上，LED0接到GPIO3上

1. STM32 IO 初始化流程
- 使能GPIO时钟
- 设置IO复用，将其复用为GPIO
- 配置GPIO的电气属性
- 使用GPIO，输出高/低电平

2. I.MX6ULL IO 初始化流程
- 使能时钟：**CCGR0-6**这七个寄存器控制6ULL所有外设时钟的使能
![CCGR0-6](https://github.com/sybc120404/image4md/blob/main/ccgr0_6.png)
- 设置IO复用，如下图，设置SW_MUX_CTL_PAD_GPIO1_IO03 SW MUX Control
Register 值为`0b0101`
![gpio_1_3_1](https://github.com/sybc120404/image4md/blob/main/gpio_1_3_1.png)
![gpio_1_3_2](https://github.com/sybc120404/image4md/blob/main/gpio_1_3_2.png)
- 配置电气属性：配置寄存器，详情查看 32.6.156 SW_PAD_CTL_PAD_GPIO1_IO03 SW PAD Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03)
