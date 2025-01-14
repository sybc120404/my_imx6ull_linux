/**
 * @file    ccm.h
 * @brief   c header file of ccm module.
 *
 * 
 * 
 * @author  Cai
 * @date    13Jan2025
 */

#ifndef __CCM_H_
#define __CCM_H_

/**
 * @brief Include files for the CCM module.
 */

#include "common.h"

/**
 * @brief Typedefs for the CCM module.
 */

typedef struct
{
    __IO uint32_t CCR;
    __IO uint32_t CCDR;
    __IO uint32_t CSR;
    __IO uint32_t CCSR;
    __IO uint32_t CACRR;
    __IO uint32_t CBCDR;
    __IO uint32_t CBCMR;
    __IO uint32_t CSCMR1;
    __IO uint32_t CSCMR2;
    __IO uint32_t CSCDR1;
    __IO uint32_t CS1CDR;
    __IO uint32_t CS2CDR;
    __IO uint32_t CDCDR;
    __IO uint32_t CHSCCDR;
    __IO uint32_t CSCDR2;
    __IO uint32_t CSCDR3;
    __IO uint32_t RESERVED0[2];
    __IO uint32_t CDHIPR;
    __IO uint32_t RESERVED1[2];
    __IO uint32_t CLPCR;
    __IO uint32_t CISR;
    __IO uint32_t CIMR;
    __IO uint32_t CCOSR;
    __IO uint32_t CGPR;
    __IO uint32_t CCGR0;
    __IO uint32_t CCGR1;
    __IO uint32_t CCGR2;
    __IO uint32_t CCGR3;
    __IO uint32_t CCGR4;
    __IO uint32_t CCGR5;
    __IO uint32_t CCGR6;
    __IO uint32_t RESERVED2[1];
    __IO uint32_t CMEOR;
} CCM_TYPE;

typedef struct 
{
    __IO uint32_t PLL_ARM;
    __IO uint32_t PLL_ARM_SET;
    __IO uint32_t PLL_ARM_CLR;
    __IO uint32_t PLL_ARM_TOG;
    __IO uint32_t PLL_USB1;
    __IO uint32_t PLL_USB1_SET;
    __IO uint32_t PLL_USB1_CLR;
    __IO uint32_t PLL_USB1_TOG;
    __IO uint32_t PLL_USB2;
    __IO uint32_t PLL_USB2_SET;
    __IO uint32_t PLL_USB2_CLR;
    __IO uint32_t PLL_USB2_TOG;
    __IO uint32_t PLL_SYS;
    __IO uint32_t PLL_SYS_SET;
    __IO uint32_t PLL_SYS_CLR;
    __IO uint32_t PLL_SYS_TOG;
    __IO uint32_t PLL_SYS_SS;
    __IO uint32_t RESERVED_1[3];
    __IO uint32_t PLL_SYS_NUM;
    __IO uint32_t RESERVED_2[3];
    __IO uint32_t PLL_SYS_DENOM; 
    __IO uint32_t RESERVED_3[3];
    __IO uint32_t PLL_AUDIO;
    __IO uint32_t PLL_AUDIO_SET;
    __IO uint32_t PLL_AUDIO_CLR;
    __IO uint32_t PLL_AUDIO_TOG;
    __IO uint32_t PLL_AUDIO_DENOM;
    __IO uint32_t RESERVED_4[3];
    __IO uint32_t PLL_VIDEO;
    __IO uint32_t PLL_VIDEO_SET;
    __IO uint32_t PLL_VIDEO_CLR;
    __IO uint32_t PLL_VIDEO_TOG;
    __IO uint32_t PLL_VIDEO_NUM;
    __IO uint32_t RESERVED_5[3];
    __IO uint32_t PLL_VIDEO_DENOM;
    __IO uint32_t RESERVED_6[7];
    __IO uint32_t PLL_ENET;
    __IO uint32_t PLL_ENET_SET;
    __IO uint32_t PLL_ENET_CLR;
    __IO uint32_t PLL_ENET_TOG;
    __IO uint32_t PFD_480;
    __IO uint32_t PFD_480_SET;
    __IO uint32_t PFD_480_CLR;
    __IO uint32_t PFD_480_TOG;
    __IO uint32_t PFD_528;
    __IO uint32_t PFD_528_SET;
    __IO uint32_t PFD_528_CLR;
    __IO uint32_t PFD_528_TOG;
    __IO uint32_t RESERVED_7[16];
    __IO uint32_t MISC0;
    __IO uint32_t MISC0_SET;
    __IO uint32_t MISC0_CLR;
    __IO uint32_t MISC0_TOG;
    __IO uint32_t MISC1;
    __IO uint32_t MISC1_SET;
    __IO uint32_t MISC1_CLR;
    __IO uint32_t MISC1_TOG;
    __IO uint32_t MISC2;
    __IO uint32_t MISC2_SET;
    __IO uint32_t MISC2_CLR;
    __IO uint32_t MISC2_TOG;
} CCM_ANALOG_TYPE;

/**
 * @brief Macro definitions for the CCM module.
 */

#define     CCM_BASE                (0x020c4000)
#define     CCM_ANALOG_BASE			(0X020C8000)

#define     CCM                     ((CCM_TYPE *)CCM_BASE)
#define     CCM_ANALOG              ((CCM_ANALOG_TYPE *)CCM_ANALOG_BASE)

/**
 * @brief Function declaration for the CCM module.
 */

/**
 * @brief Sets a value to a specified address in the CCM (Clock Control Module).
 *
 * This function writes a given value to a specified address in the CCM.
 *
 * @param addr  Pointer to the address where the value will be set.
 * @param value The value to be set at the specified address.
 *
 * @return An integer indicating the success or failure of the operation.
 */
int ccm_reg_set_value(__IO uint32_t *addr, uint32_t value);

#endif