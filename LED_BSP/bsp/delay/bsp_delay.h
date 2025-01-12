#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* 短延时 */
void delay_short(volatile unsigned int n);

/* 延时，主频396MHz时，一次循环大概1ms */
void delay(volatile unsigned int n);

#ifdef __cplusplus
}
#endif

#endif