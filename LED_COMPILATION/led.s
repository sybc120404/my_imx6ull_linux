.global _start  @全局标号，程序入口

_start:

    @ 使能gpio3时钟
    ldr r0, =0x020c4070     @将0x020C4070的地址（CCGR2）加载到r0寄存器
    ldr r1, =0x0c000000     @将0x0C000000的地址加载到r1寄存器（bit27-26=0b11）
    str r1, [r0]            @将r1的值写入r0指向的地址（CCGR2）

    @ 设置IO复用
    ldr r0, =0x020e0068
    ldr r1, =0x00000005
    str r1, [r0]

    @ 设置电气属性
    ldr r0, =0x020e02f4
    ldr r1, =0x000010b0
    str r1, [r0]

    @ 设置GPIO01_IO03输出
    ldr r0, =0x0209c004
    ldr r1, =0x8
    str r1, [r0]

    @ 设置GPIO01_IO03输出低电平
    ldr r0, =0x0209c000
    ldr r1, =0x0
    str r1, [r0]

loop:
    b loop