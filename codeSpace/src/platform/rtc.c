/*
    File:   rtc.c
    Des:    c file of rtc module
    Date:   16Feb25
    Author: Cai
*/

/*
    Include Files
*/

#include "rtc.h"
#include "debug.h"

/*
    Global variable
*/

rtc_date_time rtcDate = {
    2021,10,5,0,0,0
};

/*
    Global funcs
*/

/* 判断是否闰年 */
static unsigned char rtc_isleapyear(unsigned short year)
{	
	unsigned char value=0;
	
	if(year % 400 == 0)
		value = 1;
	else 
	{
		if((year % 4 == 0) && (year % 100 != 0))
			value = 1;
		else 
			value = 0;
	}
	return value;
}

/* 日期转换秒数 */
static uint64_t rtc_date_to_sec(rtc_date_time *datetime)
{
    unsigned short i = 0;
	uint64_t seconds = 0;
	unsigned int days = 0;
	unsigned short monthdays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
	
    if(NULL == datetime)
    {
        DBG_ERR("BAD_PARA");
        return 0;
    }

	for(i = 1970; i < datetime->year; i++)
	{
		days += DAY_PER_YEAR; 		/* 平年，每年365天 */
		if(rtc_isleapyear(i)) days += 1;/* 闰年多加一天 		*/
	}

	days += monthdays[datetime->month];
	if(rtc_isleapyear(i) && (datetime->month >= 3)) days += 1;/* 闰年，并且当前月份大于等于3月的话加一天 */

	days += datetime->day - 1;

	seconds = days * SEC_PER_DAY + 
				datetime->hour * SEC_PER_HOUR +
				datetime->minute * SEC_PER_MIN +
				datetime->second;

	return seconds;	
}

static void sec_to_rtc_date(uint64_t seconds, rtc_date_time *datetime)
{
    u64 x = 0;
    u64 secondsRemaining = 0, days = 0;
    unsigned short daysInYear = 0;

    /* 每个月的天数 */
    unsigned char daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    if(NULL == datetime)
    {
        DBG_ERR("BAD PARAM");
    }

    secondsRemaining = seconds; /* 剩余秒数初始化 */
    days = secondsRemaining / SEC_PER_DAY + 1; 		/* 根据秒数计算天数,加1是当前天数 */
    secondsRemaining = secondsRemaining % SEC_PER_DAY; /*计算天数以后剩余的秒数 */

	/* 计算时、分、秒 */
    datetime->hour = secondsRemaining / SEC_PER_HOUR;
    secondsRemaining = secondsRemaining % SEC_PER_HOUR;
    datetime->minute = secondsRemaining / 60;
    datetime->second = secondsRemaining % SEC_PER_MIN;

    /* 计算年 */
    daysInYear = DAY_PER_YEAR;
    datetime->year = YEAR_START;
    while(days > daysInYear)
    {
        /* 根据天数计算年 */
        days -= daysInYear;
        datetime->year++;

        /* 处理闰年 */
        if (!rtc_isleapyear(datetime->year))
            daysInYear = DAY_PER_YEAR;
        else	/*闰年，天数加一 */
            daysInYear = DAY_PER_YEAR + 1;
    }
	/*根据剩余的天数计算月份 */
    if(rtc_isleapyear(datetime->year)) /* 如果是闰年的话2月加一天 */
        daysPerMonth[2] = 29;

    for(x = 1; x <= 12; x++)
    {
        if (days <= daysPerMonth[x])
        {
            datetime->month = x;
            break;
        }
        else
        {
            days -= daysPerMonth[x];
        }
    }

    datetime->day = days;

}

/* 读取秒数 */
static uint64_t rtc_get_seconds()
{
    uint64_t seconds = 0;

    seconds = (SNVS->LPSRTCMR << 17) | (SNVS->LPSRTCLR >> 15);

    return seconds;
}

/*
    function definition
*/

/* RTC初始化 */
void rtc_init()
{
    /*
        SNVS_HPCOMR:
        bits:
            31: 1-软件可以访问SNVS所有寄存器
            8:  和安全相关，可以1
    */
    SNVS->HPCOMR |= (1 << 31) | (1 << 8);

    rtc_set_date_time(&rtcDate);

    rtc_enable();   // 开启rtc

    DBG_ALZ_BRIEF("rtc init done");
}

/* 开启RTC */
void rtc_enable()
{
    /*
        SNVS_LPCR寄存器
        bit0:   1-使能/开启rtc
    */
    SNVS->LPCR |= 1;
    while(0 == (SNVS->LPCR & 0x1)){}
}

/* 关闭RTC */
void rtc_disable()
{
    SNVS->LPCR &= ~(1);
    while(1 == (SNVS->LPCR & 0x1)){}
}

/* 设置时间 */
void rtc_set_date_time(rtc_date_time *date_time)
{
    uint32_t tmp = SNVS->LPCR;
    uint64_t seconds = 0;

    if(NULL == date_time)
    {
        DBG_ERR("BAD PARAM");
        return;
    }

    rtc_disable();  /* 关闭rtc */

    seconds = rtc_date_to_sec(date_time);   // 计算秒数

    /*
        SNVS->LPSRTCMR：bit14-0存储高15bit秒数
        SNVS->LPSRTCLR: bit31-15存储低17bit秒数
    */
    SNVS->LPSRTCMR = (unsigned int)(seconds >> 17);  // 高15bit
    SNVS->LPSRTCLR |= (unsigned int)(seconds << 15);  // 低17bits

    /* 之前如果是打开，那么重新打开 */
    if(tmp & 0x1)
    {
        rtc_enable();
    }
}

/* 获取时间 */
void rtc_get_date_time(rtc_date_time *date_time)
{
    uint64_t seconds = 0;

    if(NULL == date_time)
    {
        DBG_ERR("BAD PARAM");
        return;
    }

    seconds = rtc_get_seconds();

    sec_to_rtc_date(seconds, date_time);
}