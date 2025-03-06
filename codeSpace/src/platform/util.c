/**
 * @file    util.c
 * @brief   c header of util module.
 *
 * 
 * 
 * @author  Cai
 * @date    06Mar2025
 */

/*
    Include Files
*/

#include "util.h"
#include <string.h>

/*
    Function Definition
*/

/* 转浮点字符串 */
ERR_CODE int_convert_float_str(int32_t data, uint8_t decimal_len, char *str, uint8_t str_len)
{
    if(NULL == str)
    {
        return ERR_BAD_PARAM;
    }

    memset(str, 0, sizeof(char) * str_len);
    
    if(data < 0)
    {
        snprintf(str + strlen(str), sizeof(str)-strlen(str), "-");
    }

    snprintf(str + strlen(str), sizeof(str)-strlen(str), "%d.%d", (data / (10*decimal_len)), (data % (10*decimal_len)));

    return ERR_NO_ERROR;
}