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
![CCGR_2_REG](https://github.com/sybc120404/image4md/blob/main/CCGR_2_REG.png)
- 设置IO复用，如下图，设置SW_MUX_CTL_PAD_GPIO1_IO03 SW MUX Control
Register 值为`0b0101`
![gpio_1_3_1](https://github.com/sybc120404/image4md/blob/main/gpio_1_3_1.png)
![gpio_1_3_2](https://github.com/sybc120404/image4md/blob/main/gpio_1_3_2.png)
- 配置电气属性：配置寄存器，详情查看 32.6.156 SW_PAD_CTL_PAD_GPIO1_IO03 SW PAD Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03)
- 设置GPIO方向：GPIO_GDIR寄存器为输出；设置GPIO输出值：GPIO_GDIR寄存器
![gpio_gdir](https://github.com/sybc120404/image4md/blob/main/GPIO_GDIR.png)
![gpio_dr](https://github.com/sybc120404/image4md/blob/main/GPIO_DR.png)

### 汇编基础

使用GCC交叉编译器，汇编代码需要符合GNU语法。GNU汇编语法适用于所有架构

每条指令有三个可选部分。其中`label`为标号，表示地址位置（注意冒号）；`instruction`为指令；`@`后面为注释
```
label: instruction @ comment
```



汇编程序的默认入口标号是`_start`
```
.global _start

_start:
        ldr r0, =0x12   @r0=0x12
```
上面`.global`是一个伪操作，表示`_start`是一个全局标号，类似C语言全局变量

GNU汇编支持函数，函数格式：
```
函数名:
    函数体
    返回语句（非必须）
```

需要注意的小细节
1. 不允许大小写混用，所有符号都可以全大写或全小写


#### 常用指令

#### 寄存器指令

##### MOV

```
(MOV dst, src)
MOV R0, R1      @寄存器R1中的数据传递给R0，即R0=R1
MOV R0, #0x12   @立即数0x12传递给R0寄存器，即R0=0x12
```

##### MRS

```
MRS R0, CPSR    @特殊寄存器CPSR中的数据传递给R0
```

##### MSR

```
MSR CPSR, R0    @CPSR=R0
```

#### 存储器访问指令

**ARM不能直接访问存储器，例如RAM类型。I.MX6ULL的寄存器就是RAM类型**
一般需要先将配置写入Rx(0-12)中，再写入存储器

以下`LDR`和`STR`指令都是按字操作，操作32bit数据
按字节操作：`LDRB`, `STRB`
按半字操作：`LDRH`, `STRH`

##### LDR

(Load Register)，从存储器加载数据到寄存器Rx中，可以加载立即数，必须使用`=`而不是`#`

```
(LDR Rd, [Rn, #offset])   @从存储器Rn+offset的位置读取数据放入Rd
LDR R0, =0x0209C004         @将寄存器地址0x0209C004写入R0
LDR R1, [R0]                @将R0位置处存储的数据加载到R1寄存器
```

**`[]`表示取出该位置存储的数据**

##### STR

(Store Register)，寄存器数据写入存储器中

```
(STR src, dst)              @注意这里源和目的
LDR R0, =0x0209C004
LDR R1, =0x20000002
STR R1, [R0]                @将R1中写入的值写入到R0保存的地址中
```

#### 栈操作

包括`PUSH`和`POP`

```
PUSH <reg list>
POP <reg list>   
```

#### 跳转指令

````
B <label>           @跳转到label
BX <Rm>             @跳转到Rm中存放的地址处，并切换指令集
BL <label>          @跳转到label，返回地址保存在LR中
BLX <Rm>            @跳转到Rm指定的地址，将返回地址存放在LR中，并切换指令集
````

## 编译程序

1. 将.c .s文件编译为.o文件
```
arm-linux-gnueabihf-gcc -g -c led.s -o led.o
```
- `-g`：产生调试信息
- `-c`：编译源文件，**不链接**
- `-o`：指定编译产生的文件的名字

2. 将所有.o文件链接为可执行文件.elf

每个会汇编文件和.c文件都会生成一个.o文件，需要链接起来形成可执行文件，**链接到一个起始地址**，即代码运行的起始地址
对于6ULL，链接起始地址应该指向RAM地址，RAM分为内部RAM（0x900000~0x91ffff）和外部RAM（DDR，0x80000000起始，分256MB和512MB），一般是外部DDR，空间较大
**本系列裸机代码链接地址都在0x87800000**

```
arm-linux-gnueabihf-ld -Ttext 0x87800000 led.o -o led.elf
```
- `-Ttext`：指定链接地址
- `-o`：指定链接生成的文件名

3. 将.elf文件转为.bin文件
格式转换
```
arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
```
- `-O`：指定输出的格式，`binary`表示二进制格式输出
- `-S`：表示不要复制源文件中的重定位信息和符号信息
- `-g`：不复制源文件中的调试信息

4. 反汇编：.elf文件转为.s （方便C语言调试）
```
arm-linux-gnueabihf-objdump -D led.elf > led.dis
```

- `-D`：反汇编所有的段

以上步骤使用Makefile整理到一起

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

## 附录

![寄存器组](https://github.com/sybc120404/image4md/blob/main/REG.png)
![运行模式](https://github.com/sybc120404/image4md/blob/main/MO.png)
