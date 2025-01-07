.global _start  @全局标号，程序入口

_start:

    @ 使能gpio3时钟
	ldr r1, =0xffffffff
	ldr r0, =0x020c4070  	/* CCGR2 */
	str r1, [r0]

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
