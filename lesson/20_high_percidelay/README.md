# high_percidelay

使用空指令循环延时不准确！且随着系统主频修改，时间也会变化

本节使用6ULL的GPT定时器来实现高精度延时，不随着主频变化而变化

GPT是32bit的向上计数器，有捕获功能，支持比较输出和中断功能；有12bit分频器

如下图，我们可以使用ipg_clk作为时钟源，之前已配置66MHz

![GPT](https://github.com/sybc120404/image4md/blob/main/GPT.png)

GPT定时器有三路比较输出，两种工作模式

1. restart模式：计数值和比较寄存器的值相等时，从0x0开始计时（只有比较通道1才有此功能）
2. free-run模式：计数器从0x0到0xffffffff计数，所有三个输出比较通道都适用


## 代码编写

本章使用GPT定时器实现高精度延时，代码位于[gpt](../../codeSpace/src/app/gpt/gpt.c)，时延封装一层放在[delay](../../codeSpace/src/platform/delay.c)中

```c
gpt1_timer_init();      // 用作定时器的初始化，和epit用法一致
gpt1_counter_init();    // 使用计数来实现高精度延时
```