/**
 * @file    delay.c
 * @brief   c file of delay module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

/**
 * @brief Include files for the delay module.
 */

#include "delay.h"
#include "gpt.h"

/**
 * @brief Function definition for the GPIO module.
 */

void delay_short(volatile unsigned int n)
{
    while(n--){}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

/* us级别的时延，必须确保已调用gpt1_counter_init!!! */
void delay_us(uint32_t us)
{
    uint32_t oldCnt = 0;
    uint32_t newCnt = 0;
    uint32_t cntVal = 0;
    
    oldCnt = GPT1->CNT;
    while(1)
    {
        newCnt = GPT1->CNT;
        if(newCnt != oldCnt)
        {
            if(newCnt > oldCnt)
            {
                cntVal += (newCnt - oldCnt);
            }
            else
            {
                cntVal += (0xffffffff - oldCnt + newCnt + 1);   /* newCnt溢出的情况 */
            }
            oldCnt = newCnt;
        }

        if(cntVal >= us)
        {
            break;
        }
    }
}

/* 毫秒级别延时 */
void delay_ms(uint32_t ms)
{
    uint32_t i = 0;
    for(; i< ms; ++ i)
        delay_us(1000);
}