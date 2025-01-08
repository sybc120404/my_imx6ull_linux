#ifndef __LED_H
#define __LED_H

#define CCGR2 (*(volatile unsigned int *)0x020c4070)    /* CCGR2寄存器值 */

#define SW_MUX_GPIO1_IO03 (*(volatile unsigned int *)0x020e0068)    /* 复用寄存器 */
#define SW_PAD_GPIO1_IO03 (*(volatile unsigned int *)0x020e02f4)    /* 配置寄存器 */

#define GPIO1_DR    (*(volatile unsigned int *)0x0209c000)    /* 数据寄存器 */
#define GPIO1_GDIR  (*(volatile unsigned int *)0x0209c004)    /* 方向寄存器 */

#endif