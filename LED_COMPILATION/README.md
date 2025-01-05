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

