/*
    File:   sysLog.c
    Des:    c file of sysLog module
    Date:   07Mar25
    Author: Cai
*/

/*
    添加日志，请在
    1. sysLog.h文件，SYS_LOG_ID中添加日志ID
    2. 在sys_log_id_to_str接口添加日志ID对应字符串
*/

/*
    Include files
*/

#include "sysLog.h"
#include <string.h>

/*
    Global variables
*/

SYS_LOG_STRUCT syslog = {};

/*
    Private Function Definition
*/

static char* sys_log_mod_to_str(SYS_LOG_MOD mod)
{
    switch(mod)
    {
        case SYS_LOG_MOD_LED:
            return "LED";
        case SYS_LOG_MOD_KEY:
            return "KEY";
        case SYS_LOG_MOD_UART:
            return "UART";
        case SYS_LOG_MOD_AP3216C:
            return "AP3216C";
        default:
            return "UNKNOWN";
    }

    return "";
}

static char *sys_log_level_to_str(SYS_LOG_LEVEL level)
{
    switch(level)
    {
        case SYS_LOG_LEVEL_DEBUG:
            return "DEBUG";
        case SYS_LOG_LEVEL_INFO:
            return "INFO";
        case SYS_LOG_LEVEL_WARNING:
            return "WARNING";
        case SYS_LOG_LEVEL_ERROR:
            return "ERROR";
        case SYS_LOG_LEVEL_FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }

    return "";
}

/*
    Macro Definition
*/

#define SYS_LOG_STATUS_LOCK        (1)
#define SYS_LOG_STATUS_UNLOCK      (0)

#define SYS_LOG_LOCK      do{ \
    while(SYS_LOG_STATUS_LOCK == syslog.lock)  {}   \
    syslog.lock = SYS_LOG_STATUS_LOCK; \
}while(0);

#define SYS_LOG_UNLOCK    do{ \
    syslog.lock = SYS_LOG_STATUS_UNLOCK; \
}while(0);

/*
    Function Definition
*/

/* 日志初始化 */
ERR_CODE sys_log_init()
{
    memset(&syslog, 0, sizeof(SYS_LOG_STRUCT));

    DBG_ALZ_BRIEF("sysLog init done.\r\n");
    return ERR_NO_ERROR;
}

/* 添加日志 */
ERR_CODE sys_log_add(SYS_LOG_LEVEL level, SYS_LOG_MOD mod, char *logStr)
{
    uint8_t pos = 0;
     
    if(level >= SYS_LOG_LEVEL_MAX)
    {
        DBG_ERR("sysLog level error.\r\n");
        return ERR_SYS_LOG_LEVEL_ERR;
    }

    if(mod > SYS_LOG_MOD_END)
    {
        return ERR_SYS_LOG_STR_ERR;
    }

    if(NULL == logStr || strlen(logStr) >= SYS_LOG_STR_MAX_LEN)
    {
        return ERR_SYS_LOG_STR_ERR;
    }

    SYS_LOG_LOCK

    pos = (syslog.head + syslog.logNum) % SYS_LOG_MAX_NUM;

    if(syslog.logNum < SYS_LOG_MAX_NUM)
    {
        syslog.logNum++;
    }
    else
    {
        syslog.head = (syslog.head + 1) % SYS_LOG_MAX_NUM;
    }

    syslog.logContent[pos].level = level;
    syslog.logContent[pos].mod = mod;
    memcpy(syslog.logContent[pos].logStr, logStr, SYS_LOG_STR_MAX_LEN);

    SYS_LOG_UNLOCK

    return ERR_NO_ERROR;
}

/* 打印日志 */
ERR_CODE sys_log_display_all()
{
    uint8_t i = 0;
    uint8_t pos = 0;

    SYS_LOG_LOCK

    printf("syslog num: %d\r\n", syslog.logNum);

    for(i = 0; i < syslog.logNum; i++)
    {
        pos = (syslog.head + i) % SYS_LOG_MAX_NUM;
        printf("[%s]<%s> - %s\r\n", sys_log_mod_to_str(syslog.logContent[pos].mod), sys_log_level_to_str(syslog.logContent[pos].level), syslog.logContent[pos].logStr);
    }

    SYS_LOG_UNLOCK

    return ERR_NO_ERROR;
}