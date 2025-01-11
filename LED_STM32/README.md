# LED_STM32

本实验主要是规范代码书写，提高之前实验代码的可读性和可维护性

## 硬件寄存器地址访问方式

通过结构体和宏，将所有内存连续的寄存器整合在一起，实现便捷的访问

例如如下CCM寄存器，查阅芯片手册可得知这些寄存器位置连续，那么可以使用一个结构体，其成员为32bit，利用C语言结构体成员存放在内存连续位置的特点，使用**base+offset**的方式表示所有寄存器
注意可能有一些超过32bit的寄存器，这种情况必须添加保留字段成员

```
#define     CCM_BASE                    (0x020c4000)
typedef struct
{
    __IO uint32_t CCR;
    __IO uint32_t CCDR;
    __IO uint32_t CSR;
    __IO uint32_t CCSR;
    __IO uint32_t CACRR;
    __IO uint32_t CBCDR;
    __IO uint32_t CBCMR;
    __IO uint32_t CSCMR1;
    __IO uint32_t CSCMR2;
    __IO uint32_t CSCDR1;
    __IO uint32_t CS1CDR;
    __IO uint32_t CS2CDR;
    __IO uint32_t CDCDR;
    __IO uint32_t CHSCCDR;
    __IO uint32_t CSCDR2;
    __IO uint32_t CSCDR3;
    __IO uint32_t RESERVED0[2];
    __IO uint32_t CDHIPR;
    __IO uint32_t RESERVED1[2];
    __IO uint32_t CLPCR;
    __IO uint32_t CISR;
    __IO uint32_t CIMR;
    __IO uint32_t CCOSR;
    __IO uint32_t CGPR;
    __IO uint32_t CCGR0;
    __IO uint32_t CCGR1;
    __IO uint32_t CCGR2;
    __IO uint32_t CCGR3;
    __IO uint32_t CCGR4;
    __IO uint32_t CCGR5;
    __IO uint32_t CCGR6;
    __IO uint32_t RESERVED2[1];
    __IO uint32_t CMEOR;
} CCM_TYPE;
#define     CCM                         ((CCM_TYPE *)CCM_BASE)

CCM->CCGR2 = 0x10000000;        // 直接设置CCGR2寄存器的值
```

## 汇编语句解释

---
```
SECTIONS{
    . = 0x87800000;
    .text :
    {
        start.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rodata)}
    .data ALIGN(4) : {*(.rodata)}

    __bss_start = .;
    .bss ALIGN(4) : {*(.bss) *(COMMON)}
    __bss_end = .;
}
```
上一个例程中，链接脚本中记录了`__bss_start`和`__bss_end`的位置，`.s`文件中可以用其实现`bss`段初始化的功能，需要如下书写才可以使用这两个符号：

```assembly
_bss_start:
    .word __bss_start
```

`_bss_start`:：这是一个标签，用于标记一个内存位置。标签在汇编代码中用于标识代码或数据的特定位置，方便在其他地方引用。
`.word __bss_start`：这是一个伪指令，表示在当前位置存储一个32位的值。这里存储的值是符号`__bss_start`的地址。
在ARM汇编中，`.word`指令用于分配一个32位的内存单元，并将指定的值存储在其中。`__bss_start`通常是链接器定义的符号，表示BSS段（未初始化数据段）的起始地址。

总结来说，这段代码的作用是将BSS段的起始地址存储在标签`_bss_start`的位置，以便在程序的其他部分可以引用这个地址。

---

```
stmia r0!, {r2}
```

这句指令是 ARM 汇编语言中的一条存储多寄存器指令。具体来说，`stmia r0!, {r2}` 的含义如下：

`stmia`：这是 "Store Multiple Increment After" 的缩写。它表示将多个寄存器的值存储到内存中，并在每次存储后递增基址寄存器。
`r0!`：`r0` 是基址寄存器，`!` 表示在执行完指令后更新 `r0` 的值。
`{r2}`：这是一个寄存器列表，表示要存储的寄存器。在这个例子中，只包含 `r2`。
具体执行过程如下：

将寄存器`r2`的值存储到 `r0` 指向的内存地址。
将 `r0` 的值递增 `4`（因为 ARM 寄存器是 32 位的，每个寄存器占 4 字节）。
总结： 这条指令的作用是将 `r2` 的值存储到 `r0` 当前指向的内存地址，然后将 `r0` 的值增加 `4`，以便指向下一个内存地址。

---

```
cmp r0, r1
ble bss_loop
```

这两行代码是用ARM汇编语言编写的，主要用于比较两个寄存器的值并根据比较结果进行条件跳转。

cmp r0, r1：这条指令用于比较寄存器 r0 和 r1 的值。它实际上是执行 r0 - r1 的操作，但不存储结果，只更新条件标志（如零标志、负标志等）。

ble bss_loop：这条指令是条件跳转指令，意思是“如果比较结果为小于或等于（Less than or Equal），则跳转到标签 bss_loop”。ble 是 "Branch if Less than or Equal" 的缩写。

总结：

如果 r0 的值小于或等于 r1 的值，程序将跳转到 bss_loop 标签处继续执行。
如果 r0 的值大于 r1 的值，程序将继续执行下一条指令。