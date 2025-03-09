/*
    File:   rtc.h
    Des:    c header of rtc module
    Date:   16Feb25
    Author: Cai
*/

#ifndef __RTC_H_
#define __RTC_H_

/*
    Include files
*/

#include "6ull.h"

/*
    Macro Defines
*/

/* 与时间相关 */
#define SEC_PER_DAY     (86400)
#define SEC_PER_HOUR    (3600)
#define SEC_PER_MIN     (60)
#define DAY_PER_YEAR    (365)
#define YEAR_START      (1970)
#define YEAR_END        (2099)


/*
    Typedef
*/

typedef struct _rtc_date_time
{
    unsigned short  year;
    unsigned char   month;
    unsigned char   day;
    unsigned char   hour;
    unsigned char   minute;
    unsigned char   second;
}rtc_date_time;

/*
    Function declaration
*/

/* RTC初始化 */
void rtc_init();

/* 开启RTC */
void rtc_enable();

/* 关闭RTC */
void rtc_disable();

/* 设置时间 */
void rtc_set_date_time(rtc_date_time *date_time);

/* 获取时间 */
void rtc_get_date_time(rtc_date_time *date_time);

#endif