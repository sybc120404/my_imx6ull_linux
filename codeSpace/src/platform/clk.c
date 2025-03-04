/**
 * @file    clk.c
 * @brief   c file of clk module.
 *
 * 
 * 
 * @author  Cai
 * @date    03Feb2025
 */

/**
 * @brief Include files
 */

#include "clk.h"

void clk_enable()
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

void imx6ull_clkInit()
{
    uint32_t pfd_reg_val = 0;

    /* 1. 初始化PLL1 6ULL系统主频528Mhz */
    
    /* 切换使用step_clk */
    if(0 == ((CCM->CCSR >> 2) & 0x1))   /* 当前ARM_PLL使用pll1_main_clk */
    {
        CCM->CCSR &= ~(1 << 8);     /* 设置step_clk使用osc_clk=24M */
        CCM->CCSR |= (1 << 2);      /* pll1_sw_clk = step_clk */
    }

    CCM_ANALOG->PLL_ARM = ((88 << 0) & 0x7f) | (1 << 13);     /* 设置分频，ENABLE位=1使能时钟输出 */
    /* 设置二分频 */
    CCM->CACRR = 1;

    /* 切换回pll1_main_clk */
    CCM->CCSR &= ~(1 << 2);

    /* PLL2 PLL3 固定频率，无需初始化 */
    /* PFD需要设置，推荐值 */
    /*
        PLL2_PFD0       352MHz
        PLL2_PFD1       594MHz
        PLL2_PFD2       394MHz
        PLL2_PFD3       297MHz
        PLL3_PFD0       720MHz
        PLL3_PFD1       540MHz
        PLL3_PFD2       508.2MHz
        PLL3_PFD3       454.7MHz
    */

    /* 528*18/FRAC = PFD */
    pfd_reg_val = CCM_ANALOG->PFD_528;
    pfd_reg_val &= ~(0x3f3f3f3f);       /* frac位清零 */
    pfd_reg_val |= ((32 & 0xff) << 24);
    pfd_reg_val |= ((24 & 0xff) << 16);
    pfd_reg_val |= ((16 & 0xff) << 8);
    pfd_reg_val |= (27 & 0xff);
    CCM_ANALOG->PFD_528 = pfd_reg_val;

    /* 480*18/FRAC = PFD */
    pfd_reg_val = CCM_ANALOG->PFD_480;
    pfd_reg_val &= ~(0x3f3f3f3f);       /* frac位清零 */
    pfd_reg_val |= ((19 & 0xff) << 24);
    pfd_reg_val |= ((17 & 0xff) << 16);
    pfd_reg_val |= ((16 & 0xff) << 8);
    pfd_reg_val |= (12 & 0xff);
    CCM_ANALOG->PFD_480= pfd_reg_val;

    /* 设置AHB_CLK_ROOT = 132MHz */
    CCM->CBCMR &= ~(3 << 18);
    CCM->CBCMR |= 1 << 18;
    CCM->CBCDR &= ~(1 << 25);
    while(CCM->CDHIPR & (1 << 5));

    /* 以下代码有问题，SDK指出有不可预知错误。实际上默认3分频，无需手动设置 */
#if 0
    CCM->CBCDR &= ~(7 << 10);
    CCM->CBCDR |= (2 << 10);    /* 3分频 */
    while(CCM->CDHIPR & (1 << 1));  /* 等待握手信号 */
#endif

    /* 设置IPG_CLK_ROOT=66MHz */
    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= (1 << 8);     /* 2分频 */

    /* 设置PER_CLK_ROOT=66MHz */
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(0x3f);     /* 1分频 */

    /* UART1添加，设置UART1_ROOT为80MHz */
    CCM->CSCDR1 &= ~(1 << 6);
    CCM->CSCDR1 &= ~(0x3f);

    /* 设置ECSPI根时钟为PLL3_60MHz */
    CCM->CSCDR2 &= ~(1 << 18);  // 60MHz
    CCM->CSCDR2 &= ~(0x3f << 19);   // 1分频
}
