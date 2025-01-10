
#define     __IO    volatile

#define     CCM_BASE_ADDR   (0x020c4000)    /* CCM外设基地址 */

typedef unsigned int uint32_t;

/* CCM外设 */
typedef struct
{
    __IO uint32_t CCR;
    __IO uint32_t CCDR;
    __IO uint32_t CSR;
    __IO uint32_t CCSR;
    __IO uint32_t CACRR;
    __IO uint32_t CBCDR;
    __IO uint32_t CBCMR;
    __IO uint32_t CSCMR1;
    __IO uint32_t CSCMR2;
    __IO uint32_t CSCDR1;
    __IO uint32_t CS1CDR;
    __IO uint32_t CS2CDR;
    __IO uint32_t CDCDR;
    __IO uint32_t CHSCCDR;
    __IO uint32_t CSCDR2;
    __IO uint32_t CSCDR3;
    __IO uint32_t RESERVED0[2];
    __IO uint32_t CDHIPR;
    __IO uint32_t RESERVED1[2];
    __IO uint32_t CLPCR;
    __IO uint32_t CISR;
    __IO uint32_t CIMR;
    __IO uint32_t CCOSR;
    __IO uint32_t CGPR;
    __IO uint32_t CCGR0;
    __IO uint32_t CCGR1;
    __IO uint32_t CCGR2;
    __IO uint32_t CCGR3;
    __IO uint32_t CCGR4;
    __IO uint32_t CCGR5;
    __IO uint32_t CCGR6;
    __IO uint32_t RESERVED2[1];
    __IO uint32_t CMEOR;
}CCM_TYPE;

/* ------------- 定义访问寄存器的指针 ------------- */
#define CCM    ((CCM_TYPE *)CCM_BASE_ADDR)