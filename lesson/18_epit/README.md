# EPIT TIMER

本章是EPIT定时器的例程

## EPIT定时器原理

Enhanced Periodic Interrupt Timer，增强型周期中断定时器，原理图如下：

![EPIT](https://github.com/sybc120404/image4md/blob/main/EPIT.png)

1. EPIT是一个32bit的向下计数器
2. 时钟来源可选，我们选择ipg_clk，在[14_clk](../14_clk/README.md)中已经设置66MHz
3. 可以再进行12bit的分频
4. 开启EPIT后，计数寄存器会每个时钟-1，直到和比较寄存器计数值相等时，触发中断

**6ULL有两个EPIT定时器，分别是`EPIT1`和`EPIT2`**

EPIT有两种工作模式
- set-and-forget，计数结束后从EPIT_LR寄存器设置的值开始
- free-running，计数结束后从0xffffffff开始

通过EPIT_CR寄存器配置来控制

![EPITCR1](https://github.com/sybc120404/image4md/blob/main/EPITCR1.png)
![EPITCR2](https://github.com/sybc120404/image4md/blob/main/EPITCR2.png)

