/**
 * @file    iomux.c
 * @brief   c file of iomux module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

/**
 * @brief Include files for the IOMUX module.
 */

#include "iomux.h"

/**
 * @brief STATIC Function definition for the IOMUX module.
 */

/**
 * @brief Function definition for the IOMUX module.
 */

int iomux_mux_reg_set_value(__IO uint32_t *addr, uint32_t value)
{
    if(NULL == addr || addr < IOMUX_SW_MUX_BASE || addr >= (IOMUX_SW_MUX_BASE + sizeof(IOMUX_SW_MUX_TYPE)))
    {
        printf("error addr\r\n");
        return -1;
    }

    *addr = value;

    return 0;
}

int iomux_pad_reg_set_value(__IO uint32_t *addr, uint32_t value)
{
    if(NULL == addr || addr < IOMUX_SW_PAD_BASE || addr >= (IOMUX_SW_PAD_BASE + sizeof(IOMUX_SW_PAD_TYPE)))
    {
        printf("error addr\r\n");
        return -1;
    }

    *addr = value;

    return 0;
}