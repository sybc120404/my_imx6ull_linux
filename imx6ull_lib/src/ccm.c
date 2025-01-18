/**
 * @file    ccm.c
 * @brief   c file of ccm module.
 *
 * 
 * 
 * @author  Cai
 * @date    14Jan2025
 */

/**
 * @brief Include files for the CCM module.
 */

#include "ccm.h"

/**
 * @brief STATIC Function definition for the CCM module.
 */

/**
 * @brief Function definition for the CCM module.
 */

int ccm_reg_set_value(__IO uint32_t *addr, uint32_t value)
{
    if(NULL == addr)
    {
        return -1;
    }

    *addr = value;

    return 0;
}