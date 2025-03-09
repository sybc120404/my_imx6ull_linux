/**
 * @file    util.h
 * @brief   c header file of util module.
 *
 * 
 * 
 * @author  Cai
 * @date    06Mar2025
 */

#ifndef __UTIL_H_
#define __UTIL_H_

/*
    Include Files    
*/

#include "debug.h"
#include "6ull.h"

/*
    Function Declaration
*/

/* 转浮点字符串 */
ERR_CODE int_convert_float_str(int32_t data, uint8_t decimal_len, char *str, uint8_t str_len);

#endif