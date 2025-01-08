.global _start

_start:
    @ 设置处理器SVC模式
    MRS R0, CPSR                @ 读取当前处理器状态寄存器
    AND R0, R0, #0xffffffe0     @ 清除CPSR的M[4:0]
    ORR R0, R0, #0x00000013     @ 设置处理器SVC模式
    MSR CPSR, R0                @ 设置处理器状态寄存器

    @ 设置堆栈指针
    LDR R0, =0x80200000        @ 设置堆栈指针

    @ 跳转到C语言main函数
    b main

