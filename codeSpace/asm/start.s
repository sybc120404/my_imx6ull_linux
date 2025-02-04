.global _start
.global _bss_start
.global _bss_end

_start:

    ldr pc, =Reset_Handler      /* 复位中断服务函数 */
    ldr pc, =Undefined_Handler  /* 未定义指令中断服务函数 */
    ldr pc, =SVC_Handler        /* SVC中断服务函数 */
    ldr pc, =RreAbort_Handler   /* 预取终止中断服务函数 */
    ldr pc, =DataAbort_Handler  /* 数据终止中断服务函数 */
    ldr pc, =NotUsed_Handler    /* 未使用中断服务函数 */
    ldr pc, =IRQ_Handler        /* IRQ中断服务函数 */
    ldr pc, =FIQ_Handler        /* FIQ中断服务函数 */

Reset_Handler:

    /* 关闭IRQ中断 */
    cpsid i

    /* 关闭ICache，DCache和MMU */
    /* 修改SCTLR寄存器 */
    mrc p15, 0, r0, c1, c0, 0   /* 读取SCTLR寄存器数据到r0 */
    bic r0, r0, #(1 << 12)
    bic r0, r0, #(1 << 11)
    bic r0, r0, #(1 << 2)
    bic r0, r0, #(1 << 1)
    bic r0, r0, #(1 << 0)
    mcr p15, 0, r0, c1, c0, 0   /* r0寄存器数据写入SCTLR */

    /* 设置中断向量偏移 */
    ldr r0, =0x87800000
    dsb
    isb
    mcr p15, 0, r0, c12, c0, 0  /* 设备VBAR寄存器=0x87800000 */
    dsb
    isb

_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end

    /* 初始化BSS段 */
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1
    ble bss_loop

    /* 设置处理器进入SYS模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1F   /* 清除r0的bit4-0 */
    orr r0, r0, #0x1f
    msr cpsr, r0
    /* 设置SYS模式下的堆栈指针 */
    ldr sp, =0x80600000

    /* 设置处理器进入IRQ模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1F   /* 清除r0的bit4-0 */
    orr r0, r0, #0x12
    msr cpsr, r0
    /* 设置IRQ模式下的堆栈指针 */
    ldr sp, =0x80400000

    /* 设置处理器进入SVC模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1F   /* 清除r0的bit4-0 */
    orr r0, r0, #0x13
    msr cpsr, r0
    /* 设置SVC模式下的堆栈指针 */
    ldr sp, =0x80200000

    /* 打开IRQ中断 */
    cpsie i
    
    b main

    /* 无限循环 */

Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0

SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

RreAbort_Handler:
    ldr r0, =RreAbort_Handler
    bx r0

DataAbort_Handler:
    ldr r0, =DataAbort_Handler
    bx r0

NotUsed_Handler:
    ldr r0, =NotUsed_Handler
    bx r0

IRQ_Handler:
    
    push {lr}               /* 保存lr地址，lr是现场地址，可能会中断嵌套，所以需要保存 */
    push {r0-r3, r12}       /* 保存r0-r3, r12寄存器， r4-r11系统自动保存 */

    mrs r0, spsr
    push {r0}               /* 保存spsr寄存器：程序状态保存寄存器，用于保存CPSR寄存器的值 */

    mrc p15, 4, r1, c15, c0, 0  /* 读CP15的C0寄存器值到r1，实际上是CBAR寄存器值，保存了GIC寄存器组首地址，借此可访问GIC寄存器组 */
    add r1, r1, #0x2000         /* GIC的CPU接口端地址 */
    ldr r0, [r1, #0xc]          /* GICC_IAR寄存器地址，bit9-0保存当前发生中断的中断号，据此可以确定调用哪个中断服务函数 */

    push {r0, r1}

    cps #0x13               /* 进入SVC模式，允许其他中断再次进去 */

    push {lr}               /* 保存SVC模式的lr寄存器 */
    ldr r2, =system_irqHandler  /* 加载C语言中断处理函数到r2，有一个输入参数：中断号 */
    blx r2                  /* 跳转，自动传r0的值作为入参 */

    pop {lr}                /* 运行完中断服务函数，lr出栈 */
    cps #0x12               /* 进入IRQ模式 */
    pop {r0, r1}
    str r0, [r1, #0x10]     /* 中断执行完成，将GICC_IAR写入GICC_EIOR */

    pop {r0}
    msr spsr_cxsf, r0       /* 恢复spsr */

    pop {r0-r3, r12}
    pop {lr}
    subs pc, lr, #0x4       /* lr-4赋值给pc */

FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0

