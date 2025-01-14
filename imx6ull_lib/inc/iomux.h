/**
 * @file    iomux.h
 * @brief   c header file of iomux module.
 *
 * 
 * 
 * @author  Cai
 * @date    13Jan2025
 */

#ifndef __IOMUX_H_
#define __IOMUX_H_

/**
 * @brief Include files for the IOMUX module.
 */

#include "common.h"

/**
 * @brief Typedefs for the IOMUX module.
 */

typedef struct 
{
    __IO uint32_t JTAG_MOD;
    __IO uint32_t JTAG_TMS;
    __IO uint32_t JTAG_TDO;
    __IO uint32_t JTAG_TDI;
    __IO uint32_t JTAG_TCK;
    __IO uint32_t JTAG_TRST_B;
    __IO uint32_t GPIO1_IO00;
    __IO uint32_t GPIO1_IO01;
    __IO uint32_t GPIO1_IO02;
    __IO uint32_t GPIO1_IO03;
    __IO uint32_t GPIO1_IO04;
    __IO uint32_t GPIO1_IO05;
    __IO uint32_t GPIO1_IO06;
    __IO uint32_t GPIO1_IO07;
    __IO uint32_t GPIO1_IO08;
    __IO uint32_t GPIO1_IO09;
    __IO uint32_t UART1_TX_DATA;
    __IO uint32_t UART1_RX_DATA;
    __IO uint32_t UART1_CTS_B;
    __IO uint32_t UART1_RTS_B;
    __IO uint32_t UART2_TX_DATA;
    __IO uint32_t UART2_RX_DATA;
    __IO uint32_t UART2_CTS_B;
    __IO uint32_t UART2_RTS_B;
    __IO uint32_t UART3_TX_DATA;
    __IO uint32_t UART3_RX_DATA;
    __IO uint32_t UART3_CTS_B;
    __IO uint32_t UART3_RTS_B;
    __IO uint32_t UART4_TX_DATA;
    __IO uint32_t UART4_RX_DATA;
    __IO uint32_t UART5_TX_DATA;
    __IO uint32_t UART5_RX_DATA;
    __IO uint32_t ENET1_RX_DATA0;
    __IO uint32_t ENET1_RX_DATA1;
    __IO uint32_t ENET1_RX_EN;
    __IO uint32_t ENET1_TX_DATA0;
    __IO uint32_t ENET1_TX_DATA1;
    __IO uint32_t ENET1_TX_EN;
    __IO uint32_t ENET1_TX_CLK;
    __IO uint32_t ENET1_RX_ER;
    __IO uint32_t ENET2_RX_DATA0;
    __IO uint32_t ENET2_RX_DATA1;
    __IO uint32_t ENET2_RX_EN;
    __IO uint32_t ENET2_TX_DATA0;
    __IO uint32_t ENET2_TX_DATA1;
    __IO uint32_t ENET2_TX_EN;
    __IO uint32_t ENET2_TX_CLK;
    __IO uint32_t ENET2_RX_ER;
    __IO uint32_t LCD_CLK;
    __IO uint32_t LCD_ENABLE;
    __IO uint32_t LCD_HSYNC;
    __IO uint32_t LCD_VSYNC;
    __IO uint32_t LCD_RESET;
    __IO uint32_t LCD_DATA00;
    __IO uint32_t LCD_DATA01;
    __IO uint32_t LCD_DATA02;
    __IO uint32_t LCD_DATA03;
    __IO uint32_t LCD_DATA04;
    __IO uint32_t LCD_DATA05;
    __IO uint32_t LCD_DATA06;
    __IO uint32_t LCD_DATA07;
    __IO uint32_t LCD_DATA08;
    __IO uint32_t LCD_DATA09;
    __IO uint32_t LCD_DATA10;
    __IO uint32_t LCD_DATA11;
    __IO uint32_t LCD_DATA12;
    __IO uint32_t LCD_DATA13;
    __IO uint32_t LCD_DATA14;
    __IO uint32_t LCD_DATA15;
    __IO uint32_t LCD_DATA16;
    __IO uint32_t LCD_DATA17;
    __IO uint32_t LCD_DATA18;
    __IO uint32_t LCD_DATA19;
    __IO uint32_t LCD_DATA20;
    __IO uint32_t LCD_DATA21;
    __IO uint32_t LCD_DATA22;
    __IO uint32_t LCD_DATA23;
    __IO uint32_t NAND_RE_B;
    __IO uint32_t NAND_WE_B;
    __IO uint32_t NAND_DATA00;
    __IO uint32_t NAND_DATA01;
    __IO uint32_t NAND_DATA02;
    __IO uint32_t NAND_DATA03;
    __IO uint32_t NAND_DATA04;
    __IO uint32_t NAND_DATA05;
    __IO uint32_t NAND_DATA06;
    __IO uint32_t NAND_DATA07;
    __IO uint32_t NAND_ALE;
    __IO uint32_t NAND_WP_B;
    __IO uint32_t NAND_READY_B;
    __IO uint32_t NAND_CE0_B;
    __IO uint32_t NAND_CE1_B;
    __IO uint32_t NAND_CLE;
    __IO uint32_t NAND_DQS;
    __IO uint32_t SD1_CMD;
    __IO uint32_t SD1_CLK;
    __IO uint32_t SD1_DATA0;
    __IO uint32_t SD1_DATA1;
    __IO uint32_t SD1_DATA2;
    __IO uint32_t SD1_DATA3;
    __IO uint32_t CSI_MCLK;
    __IO uint32_t CSI_PIXCLK;
    __IO uint32_t CSI_VSYNC;
    __IO uint32_t CSI_HSYNC;
    __IO uint32_t CSI_DATA00;
    __IO uint32_t CSI_DATA01;
    __IO uint32_t CSI_DATA02;
    __IO uint32_t CSI_DATA03;
    __IO uint32_t CSI_DATA04;
    __IO uint32_t CSI_DATA05;
    __IO uint32_t CSI_DATA06;
    __IO uint32_t CSI_DATA07;
} IOMUX_SW_MUX_TYPE;

typedef struct 
{
    __IO uint32_t DRAM_ADDR00;
    __IO uint32_t DRAM_ADDR01;
    __IO uint32_t DRAM_ADDR02;
    __IO uint32_t DRAM_ADDR03;
    __IO uint32_t DRAM_ADDR04;
    __IO uint32_t DRAM_ADDR05;
    __IO uint32_t DRAM_ADDR06;
    __IO uint32_t DRAM_ADDR07;
    __IO uint32_t DRAM_ADDR08;
    __IO uint32_t DRAM_ADDR09;
    __IO uint32_t DRAM_ADDR10;
    __IO uint32_t DRAM_ADDR11;
    __IO uint32_t DRAM_ADDR12;
    __IO uint32_t DRAM_ADDR13;
    __IO uint32_t DRAM_ADDR14;
    __IO uint32_t DRAM_ADDR15;
    __IO uint32_t DRAM_DQM0;
    __IO uint32_t DRAM_DQM1;
    __IO uint32_t DRAM_RAS_B;
    __IO uint32_t DRAM_CAS_B;
    __IO uint32_t DRAM_CS0_B;
    __IO uint32_t DRAM_CS1_B;
    __IO uint32_t DRAM_SDWE_B;
    __IO uint32_t DRAM_ODT0;
    __IO uint32_t DRAM_ODT1;
    __IO uint32_t DRAM_SDBA0;
    __IO uint32_t DRAM_SDBA1;
    __IO uint32_t DRAM_SDBA2;
    __IO uint32_t DRAM_SDCKE0;
    __IO uint32_t DRAM_SDCKE1;
    __IO uint32_t DRAM_SDCLK0_P;
    __IO uint32_t DRAM_SDQS0_P;
    __IO uint32_t DRAM_SDQS1_P;
    __IO uint32_t DRAM_RESET;
    __IO uint32_t TEST_MODE;
    __IO uint32_t POR_B;
    __IO uint32_t ONOFF;
    __IO uint32_t SNVS_PMIC_ON_REQ;
    __IO uint32_t CCM_PMIC_STBY_REQ;
    __IO uint32_t BOOT_MODE0;
    __IO uint32_t BOOT_MODE1;
    __IO uint32_t SNVS_TAMPER0;
    __IO uint32_t SNVS_TAMPER1;
    __IO uint32_t SNVS_TAMPER2;
    __IO uint32_t SNVS_TAMPER3;
    __IO uint32_t SNVS_TAMPER4;
    __IO uint32_t SNVS_TAMPER5;
    __IO uint32_t SNVS_TAMPER6;
    __IO uint32_t SNVS_TAMPER7;
    __IO uint32_t SNVS_TAMPER8;
    __IO uint32_t SNVS_TAMPER9;
    __IO uint32_t JTAG_MOD;
    __IO uint32_t JTAG_TMS;
    __IO uint32_t JTAG_TDO;
    __IO uint32_t JTAG_TDI;
    __IO uint32_t JTAG_TCK;
    __IO uint32_t JTAG_TRST_B;
    __IO uint32_t GPIO1_IO00;
    __IO uint32_t GPIO1_IO01;
    __IO uint32_t GPIO1_IO02;
    __IO uint32_t GPIO1_IO03;
    __IO uint32_t GPIO1_IO04;
    __IO uint32_t GPIO1_IO05;
    __IO uint32_t GPIO1_IO06;
    __IO uint32_t GPIO1_IO07;
    __IO uint32_t GPIO1_IO08;
    __IO uint32_t GPIO1_IO09;
    __IO uint32_t UART1_TX_DATA;
    __IO uint32_t UART1_RX_DATA;
    __IO uint32_t UART1_CTS_B;
    __IO uint32_t UART1_RTS_B;
    __IO uint32_t UART2_TX_DATA;
    __IO uint32_t UART2_RX_DATA;
    __IO uint32_t UART2_CTS_B;
    __IO uint32_t UART2_RTS_B;
    __IO uint32_t UART3_TX_DATA;
    __IO uint32_t UART3_RX_DATA;
    __IO uint32_t UART3_CTS_B;
    __IO uint32_t UART3_RTS_B;
    __IO uint32_t UART4_TX_DATA;
    __IO uint32_t UART4_RX_DATA;
    __IO uint32_t UART5_TX_DATA;
    __IO uint32_t UART5_RX_DATA;
    __IO uint32_t ENET1_RX_DATA0;
    __IO uint32_t ENET1_RX_DATA1;
    __IO uint32_t ENET1_RX_EN;
    __IO uint32_t ENET1_TX_DATA0;
    __IO uint32_t ENET1_TX_DATA1;
    __IO uint32_t ENET1_TX_EN;
    __IO uint32_t ENET1_TX_CLK;
    __IO uint32_t ENET1_RX_ER;
    __IO uint32_t ENET2_RX_DATA0;
    __IO uint32_t ENET2_RX_DATA1;
    __IO uint32_t ENET2_RX_EN;
    __IO uint32_t ENET2_TX_DATA0;
    __IO uint32_t ENET2_TX_DATA1;
    __IO uint32_t ENET2_TX_EN;
    __IO uint32_t ENET2_TX_CLK;
    __IO uint32_t ENET2_RX_ER;
    __IO uint32_t LCD_CLK;
    __IO uint32_t LCD_ENABLE;
    __IO uint32_t LCD_HSYNC;
    __IO uint32_t LCD_VSYNC;
    __IO uint32_t LCD_RESET;
    __IO uint32_t LCD_DATA00;
    __IO uint32_t LCD_DATA01;
    __IO uint32_t LCD_DATA02;
    __IO uint32_t LCD_DATA03;
    __IO uint32_t LCD_DATA04;
    __IO uint32_t LCD_DATA05;
    __IO uint32_t LCD_DATA06;
    __IO uint32_t LCD_DATA07;
    __IO uint32_t LCD_DATA08;
    __IO uint32_t LCD_DATA09;
    __IO uint32_t LCD_DATA10;
    __IO uint32_t LCD_DATA11;
    __IO uint32_t LCD_DATA12;
    __IO uint32_t LCD_DATA13;
    __IO uint32_t LCD_DATA14;
    __IO uint32_t LCD_DATA15;
    __IO uint32_t LCD_DATA16;
    __IO uint32_t LCD_DATA17;
    __IO uint32_t LCD_DATA18;
    __IO uint32_t LCD_DATA19;
    __IO uint32_t LCD_DATA20;
    __IO uint32_t LCD_DATA21;
    __IO uint32_t LCD_DATA22;
    __IO uint32_t LCD_DATA23;
    __IO uint32_t NAND_RE_B;
    __IO uint32_t NAND_WE_B;
    __IO uint32_t NAND_DATA00;
    __IO uint32_t NAND_DATA01;
    __IO uint32_t NAND_DATA02;
    __IO uint32_t NAND_DATA03;
    __IO uint32_t NAND_DATA04;
    __IO uint32_t NAND_DATA05;
    __IO uint32_t NAND_DATA06;
    __IO uint32_t NAND_DATA07;
    __IO uint32_t NAND_ALE;
    __IO uint32_t NAND_WP_B;
    __IO uint32_t NAND_READY_B;
    __IO uint32_t NAND_CE0_B;
    __IO uint32_t NAND_CE1_B;
    __IO uint32_t NAND_CLE;
    __IO uint32_t NAND_DQS;
    __IO uint32_t SD1_CMD;
    __IO uint32_t SD1_CLK;
    __IO uint32_t SD1_DATA0;
    __IO uint32_t SD1_DATA1;
    __IO uint32_t SD1_DATA2;
    __IO uint32_t SD1_DATA3;
    __IO uint32_t CSI_MCLK;
    __IO uint32_t CSI_PIXCLK;
    __IO uint32_t CSI_VSYNC;
    __IO uint32_t CSI_HSYNC;
    __IO uint32_t CSI_DATA00;
    __IO uint32_t CSI_DATA01;
    __IO uint32_t CSI_DATA02;
    __IO uint32_t CSI_DATA03;
    __IO uint32_t CSI_DATA04;
    __IO uint32_t CSI_DATA05;
    __IO uint32_t CSI_DATA06;
    __IO uint32_t CSI_DATA07;
    __IO uint32_t GRP_ADDDS;
    __IO uint32_t GRP_DDRMODE_CTL;
    __IO uint32_t GRP_B0DS;
    __IO uint32_t GRP_DDRPK;
    __IO uint32_t GRP_CTLDS;
    __IO uint32_t GRP_B1DS;
    __IO uint32_t GRP_DDRHYS;
    __IO uint32_t GRP_DDRPKE;
    __IO uint32_t GRP_DDRMODE;
    __IO uint32_t GRP_DDR_TYPE;
} IOMUX_SW_PAD_TYPE;

/**
 * @brief Macro definitions for the IOMUX module.
 */

#define     IOMUX_SW_MUX_BASE		(0X020E0044)
#define     IOMUX_SW_PAD_BASE		(0X020E0204)

#define     IOMUX_SW_MUX		    ((IOMUX_SW_MUX_TYPE *)IOMUX_SW_MUX_BASE)
#define     IOMUX_SW_PAD		    ((IOMUX_SW_PAD_TYPE *)IOMUX_SW_PAD_BASE)

/**
 * @brief Function declaration for the IOMUX module.
 */

/**
 * @brief Sets a value to a specified address in the IOMUX (Input/Output Multiplexer).
 *
 * This function writes a given value to a specified address in the IOMUX.
 *
 * @param addr  Pointer to the address where the value will be set.
 * @param value The value to be set at the specified address.
 *
 * @return An integer indicating the success or failure of the operation.
 */
int iomux_mux_reg_set_value(__IO uint32_t *addr, uint32_t value);

/**
 * @brief Sets a value to a specified address in the IOMUX pad register.
 *
 * This function writes a given value to a specified address in the IOMUX pad register.
 *
 * @param addr  Pointer to the address where the value will be set.
 * @param value The value to be set at the specified address.
 *
 * @return An integer indicating the success or failure of the operation.
 */
int iomux_pad_reg_set_value(__IO uint32_t *addr, uint32_t value);

#endif