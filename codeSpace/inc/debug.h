/*
    Author: Cai
    Data:   27Dec24
    Description:    C header of debug
*/

#include "stdio.h"

#ifndef __DEBUG_H_
#define __DEBUG_H_

/*==========================
    macro definition
*/

/* COLOR */
/*
    格式：
        起始：\033[显示方式;前景色;背景色m
        终止：\033[0m - 表示恢复默认
    起始格式选择：不需要调整的属性可以直接省略，记得分号
        显示方式：
            0(默认), 1(高亮), 22(非粗体), 4(下划线), 24(非下划线), 5(闪烁)， 25(非闪烁), 7(反显), 27(非反显)
        前景色：
            30(黑色), 31(红色), 32(绿色), 33(黄色), 34(蓝色), 35(洋红), 36(青色), 37(白色)
        背景色:
            40(黑色), 41(红色), 42(绿色), 43(黄色), ... 同上，++1
*/

#define DBG_FMT_RED             "\033[;31m"
#define DBG_FMT_BOLD_RED_YEL    "\033[1;31;43m"
#define DBG_FMT_END     "\033[0m"

/* DEBUG */
/* 0-close, 1-open */
#define DBG_ON  (1)
#if DBG_ON
/* normal debug */
#define DBG(format, ...) do{ \
    printf("[%s]<%s, %d> - " format "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);  \
}while(0);
/* always printf */
#define DBG_ALZ(format, ...)    do{ \
    printf(DBG_FMT_RED "[%s]<%s, %d> - " format DBG_FMT_END "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);  \
}while(0);
#define DBG_ALZ_BRIEF(format, ...)    do{ \
    printf(DBG_FMT_RED format DBG_FMT_END "\r\n");  \
}while(0);
/* error printf */
#define DBG_ERR(format, ...)    do{ \
    printf(DBG_FMT_BOLD_RED_YEL "[%s]<%s, %d> - " format DBG_FMT_END "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);  \
}while(0);
#else
#define DBG(format, ...)
#define DBG_ALZ(format, ...)    do{ \
    printf(DBG_FMT_RED "[%s]<%s, %d> - " format DBG_FMT_END "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);  \
}while(0);
#define DBG_ALZ_BRIEF(format, ...)  
#define DBG_ERR(format, ...)    do{ \
    printf(DBG_FMT_BOLD_RED_YEL "[%s]<%s, %d> - " format DBG_FMT_END "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);  \
}while(0);
#endif
#endif