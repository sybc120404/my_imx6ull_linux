/*
    File:   spi.h
    Des:    c header of spi module
    Date:   04Mar25
    Author: Cai
*/

#ifndef __SPI_H_
#define __SPI_H_

/*
    Include files
*/

#include "6ull.h"
#include "debug.h"

/*
    Function Declaration
*/

/* SPI初始化 */
ERR_CODE spi_init(ECSPI_Type *base);

/* SPI发送/接收 */
ERR_CODE spi_channel0_rw_byte(ECSPI_Type *base, uint8_t tx_data, uint8_t *rx_data);

#endif