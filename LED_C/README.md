# LED C VERSION

C语言版本的电灯实验

## 处理流程

### 1. 设置处理器模式

需要设置6ULL位于**SVC**模式，允许操作所有寄存器

![运行模式](https://github.com/sybc120404/image4md/blob/main/MO.png)

运行模式的设置通过**CPSR寄存器**实现，重点关注M[4:0]

![CPSR](https://github.com/sybc120404/image4md/blob/main/CPSR.png)
![CPSR1](https://github.com/sybc120404/image4md/blob/main/CPSR1.png)

CPSR寄存器属于特殊寄存器，需要使用`MRS`或`MSR`指令

### 2. 设置SP指针

> SP指针为堆栈指针，指向栈顶

SP指针可以指向内部RAM，也可以指向外部RAM（DDR），实验中我们将其指向DDR

那么SP可以设置的范围是0x80000000~0x9FFFFFFF

栈的大小指定为0x200000B=2MB，**linux是满减栈**，即高地址为栈底，低地址为栈顶，所以SP设置为0x80200000

### 3. 跳转到C语言

使用`b`指令进行跳转，跳转到C语言函数，例如`main`函数

```
B <label>           @跳转到label
```

## 分析

可以看一下反汇编生成的ledc.dis文件，0x87800000位置就是_start，之后跳转到main，按照顺序不断执行

```
Disassembly of section .text:

87800000 <_start>:
87800000:	e10f0000 	mrs	r0, CPSR
87800004:	e3c0001f 	bic	r0, r0, #31
87800008:	e3800013 	orr	r0, r0, #19
8780000c:	e129f000 	msr	CPSR_fc, r0
87800010:	e51f0000 	ldr	r0, [pc, #-0]	; 87800018 <_start+0x18>
87800014:	ea000043 	b	87800128 <__main_from_arm>
87800018:	80200000 	eorhi	r0, r0, r0

8780001c <clk_enable>:
8780001c:	b480      	push	{r7}
8780001e:	af00      	add	r7, sp, #0
87800020:	f244 0370 	movw	r3, #16496	; 0x4070
87800024:	f2c0 230c 	movt	r3, #524	; 0x20c
87800028:	f04f 32ff 	mov.w	r2, #4294967295	; 0xffffffff
8780002c:	601a      	str	r2, [r3, #0]
8780002e:	46bd      	mov	sp, r7

...
...
```

## 链接脚本

我们在`Makefile`中，执行的这一语句进行了链接。可以使用链接脚本进行更加简便，稳定的链接
```
arm-linux-gnueabihf-ld -Ttext 0x87800000 -o ledc.elf $^
```

链接脚本描述了要链接的文件，链接顺序和链接首地址，其实就是把程序进行了分段

一般程序分为四个段：`text`,`rodata`,`data`,`bss`

```
SECTIONS{
    . = 0x10000000;
    .text : {*(.text)}
    . = 0x30000000
    .data ALIGN(4) : { *(.data) }
    .bss ALIGN(4) : { *(.bss) }
}
```
- `SECTIONS{}`：链接脚本固定格式
- `.`是一个特殊符号，叫做**定位计数器**，默认值是`0`，我们对他进行了赋值
- `.text`是代码段，`.data`是数据段，`.bss`是定义了但是未初始化的变量段，一般会对bss段清零，`rodata`段是只读数据段
- `*(.text)`是指剩余的所有代码段
- `ALIGN(4)`：表示4B对齐
- `. = 0x10000000;`赋值语句必须`;`表示结尾
- `.text : {*(.text)}`：注意`:`空格，否则认为`text:`段

### 使用链接脚本

原本`Makefile`中使用
```
-Ttext 0x87800000
```
指定链接地址，自动分段，现在直接使用

```
-T(文件名)
```

注意无需空格分开，可以看本目录的Makefile这一句修改为

```
arm-linux-gnueabihf-ld -Timx6ull.lds -o ledc.elf $^
```