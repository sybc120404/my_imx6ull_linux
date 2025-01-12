#include "bsp_clk.h"

/* 使能gpio时钟 */
void clk_enable()
{
    CCM->CCGR2 = 0xffffffff;
}