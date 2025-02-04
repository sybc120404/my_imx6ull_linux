# GPIO_INTERRUPT

本章节学习GPIO中断

## STM32中断系统

### 中断向量表

中断向量表（IVT）是一个内存区域，它包含了一系列指向中断处理程序（Interrupt Handler）的指针。当发生中断时，处理器会根据中断类型在IVT中查找相应的指针，然后跳转到该指针指向的内存地址，执行中断处理程序。‌

中断包含系统中断和外部中断

### 中断向量偏移

一般ARM从0x00000000地址开始运行，但对于STM32我们设置代码链接地址为0x8000000，这部分偏移需要指出

### NVIC中断控制器

NVIC是中断管理机构，可以使能关闭指定中断、设置中断优先级

### 中断服务函数编写

即中断发生时调用的函数

## Cortex-A7中断系统

![INTERRUPT](https://github.com/sybc120404/image4md/blob/main/INTERRUPT.png)

### Cortex-A中断向量表

Cortex-A有八个中断，需要自己实现，重点关注IRQ中断（外设使用）

### 中断向量偏移

裸机例程从0x87800000开始，需要设置

### GIC中断控制器

同NVIC一样，GIC用于管理中断，可以开关中断，设置中断优先级

### IMX6U中断号

为了区分不同中断，引入中断号，CPU支持1020个中断号

**ID0-ID15分配给SGI中断（共享中断），ID16-ID31分配给PPI（私有中断），剩余ID32-ID1019给SPI中断（外部中断）**

我们重点关注SPI中断

6ULL支持128个中断，前32个留给CPU，其余的中断号已分配，使用时需要查表

## 代码编写

1. 使用按键触发中断，KEY0使用UART1_CTS

### 复位中断函数

1. 需要关闭ICache（指令Cache）、DCache（数据Cache）、MMU，确保复位前后数据一致（启动时缓存还未准备好，使能会有不可预知错误）
2. 要使用中断，则必须设置各个模式下的sp指针，如下图，User和Sys模式下公用SP指针，其他模式都是独立的

![sp](https://github.com/sybc120404/image4md/blob/main/sp.png)

3. 关闭ICache、DCache、MMU需要使用CP15协处理器。关于CP15协处理器，包含，主要用于协助内存管理，中断中也会用到，使用CP15协处理器有特殊的指令：

```
MCR    # ARM寄存器数据写入CP15
MRC {cond} p15, <opc1>, <Rt>, <CRn>, <CRm>, <opc2>    # CP15协处理器数据写入ARM寄存器
```

例如下图，要读取ID寄存器的值到ARM寄存器R0中：
```
MRC p15, 0, r0, c0, c0, 0
```

![CP15](https://github.com/sybc120404/image4md/blob/main/CP15.png)

4. 设置SCTLR寄存器

SCTLR寄存器用于控制MMU和ICache, DCache开关

![SCTLR](https://github.com/sybc120404/image4md/blob/main/SCTLR.png)

5. 设置中断向量偏移：将新的中断向量表首地址写入CP15协处理器的VBAR寄存器

![VBAR](https://github.com/sybc120404/image4md/blob/main/VBAR.png)

- DSB/ISB指令，用于清洗流水线，前面的指令都执行完才会执行后面的指令

### IRQ中断函数

1. 保存现场，包括lr，r0-r3， r12，spsr
2. GIC寄存器组

![GIC](https://github.com/sybc120404/image4md/blob/main/GIC.png)

3. 返回中断前继续执行

对于三级流水线，pc是当前执行指令地址+8，也就是取值-译码-执行，程序在取指时，pc保存的是执行的地址，中断结束后返回必须回来执行译码

```
subs pc, lr, #0x4       /* lr-4赋值给pc */
```

### 6ULL中断设置

GPIO中断

1. 首先需要设置GPIO的中断触发方式，设置GPIO_ICR1/ICR2寄存器，触发方式包括低电平、高电平、上升沿和下降沿
2. 使能GPIO对应的中断，设置GPIO_IMR寄存器
3. 处理完中断后，需要清除中断标志位，也就是设置GPIO_ISR寄存器

GIC配置

1. 使能对应中断ID，GPIO1_18对应67+32
2. 可设置中断优先级
3. 注册GOIO1_IO18中断处理函数