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

#define IN  
#define OUT 

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

#define PFM_IF_FAIL_RET(expr)   do{ \
    int rv = 0; \
    rv = expr;  \
    if(0 != rv) {   \
        printf(DBG_FMT_BOLD_RED_YEL "Call <%s,%d> error return %d" DBG_FMT_END "\r\n", __func__, __LINE__, rv); \
        return rv;  \
    }\
}while(0);

/*==========================
    error code definition
*/

typedef enum _error_code{
    ERR_NO_ERROR = 0,       // 正确
    
    ERR_BAD_PARAM = 1,      // 参数错误
    ERR_NULL_POINTER,       // 空指针

    ERR_I2C_ERR = 100,

    ERR_SPI_ERR = 200,
    ERR_SPI_TIMEOUT,        // SPI通信超时
}ERR_CODE;

#endif // end of ifdef __DEBUG_H_