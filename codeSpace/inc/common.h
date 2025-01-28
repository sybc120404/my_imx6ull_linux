/**
 * @file    ccm.h
 * @brief   c header file of common of imx6ull.
 *
 * 
 * 
 * @author  Cai
 * @date    13Jan2025
 */

#ifndef __COMMON_H_
#define __COMMON_H_

/**
 * @brief Include files for the common module.
 */

#include <stdio.h>
#include <stddef.h>

/**
 * @brief Typedefs for the common module.
 */

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed int      int32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;

typedef signed char     s8;
typedef signed short    s16;
typedef signed int      s32;
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef signed long long    s64;
typedef unsigned long long  u64;

/**
 * @brief Macro definitions for the common module.
 */

#define    __I      volatile
#define    __O      volatile
#define    __IO     volatile

#endif