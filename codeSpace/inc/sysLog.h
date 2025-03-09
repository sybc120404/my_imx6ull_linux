/*
    File:   sysLog.h
    Des:    c header of sysLog module
    Date:   07Mar25
    Author: Cai
*/

#ifndef __SYSLOG_H_
#define __SYSLOG_H_

/*
    Include files
*/

#include "common.h"
#include "debug.h"

/*
    Macro Definition
*/

#define SYS_LOG_MAX_NUM     (128)
#define SYS_LOG_STR_MAX_LEN (112)

/*
    Type Definition
*/

typedef enum sys_log_level
{
    SYS_LOG_LEVEL_DEBUG = 0,
    SYS_LOG_LEVEL_INFO,
    SYS_LOG_LEVEL_WARNING,
    SYS_LOG_LEVEL_ERROR,
    SYS_LOG_LEVEL_FATAL,
    SYS_LOG_LEVEL_MAX
}SYS_LOG_LEVEL;

typedef enum
{
    SYS_LOG_MOD_START = 0,

    SYS_LOG_MOD_LED,
    SYS_LOG_MOD_KEY,
    SYS_LOG_MOD_UART,
    SYS_LOG_MOD_AP3216C,

    SYS_LOG_MOD_END,
}SYS_LOG_MOD;    /* 日志模块ID */

/* 一条日志128B */
typedef struct sys_log_content
{
    SYS_LOG_LEVEL level : 8;
    SYS_LOG_MOD mod : 8;
    char logStr[SYS_LOG_STR_MAX_LEN];
}SYS_LOG_CONTENT;

typedef struct sys_log
{
    SYS_LOG_CONTENT logContent[SYS_LOG_MAX_NUM];    // 日志内容，数组
    uint8_t logNum;     // 当前日志数量
    uint8_t lock;       // 锁
    uint8_t head;       // 头
}SYS_LOG_STRUCT;

/*
    Function Declaration
*/

/* 日志初始化 */
ERR_CODE sys_log_init();

/* 添加日志 */
ERR_CODE sys_log_add(SYS_LOG_LEVEL level, SYS_LOG_MOD logId, char *logStr);

/* 打印日志 */
ERR_CODE sys_log_display_all();

#endif