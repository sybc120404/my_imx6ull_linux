.global _start
.global _bss_start
.global _bss_end

_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end

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
    ldr r0, =IRQ_Handler
    bx r0

FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0

