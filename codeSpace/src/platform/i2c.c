/*
    File:   i2c.c
    Des:    c file of I2C module
    Date:   23Feb25
    Author: Cai
*/

/*
    Include Files
*/

#include "i2c.h"

/*
    Function Definition
*/

/* I2C初始化 */
ERR_CODE i2c_init(I2C_Type *base)
{
    if(NULL == base)
    {
        return ERR_BAD_PARAM;
    }

    /*
        I2Cx_I2CR寄存器
        bits:
            7: 0-关闭i2c，1-使能i2c
            5: 0-slave, 1-master，从1变为0产生一个stop，从0变为1产生一个start
            4: 0-receive, 1-transmit
            3: 接受数据后，0-发送noack，1-发送ack
            2: 1-发送一个restart信号
    */
    base->I2CR &= ~(1 << 7);    // 关闭I2C

    base->IFDR = 0x15;      // 设置640分频，结果约为103.125KHz

    base->I2CR |= (1 << 7);     // 使能I2C

    return ERR_NO_ERROR;
}

/* start信号产生，从机地址，读写 */
I2C_STATUS i2c_starts(I2C_Type *base, uint8_t addr, I2C_DIRECTION direction)
{
    if(NULL == base)
    {
        return I2C_STATUS_ERROR;
    }

    // 判断是否空闲
    /*
        I2Cx_I2SR寄存器：
        bits:
            7: 0-不在传输，1-传输中
            5: 0-idle, 1-busy
            4: 1-仲裁丢失发生
            1: 中断相关
    */
    if(base->I2SR & (1 << 5))
    {
        return I2C_STATUS_BUSY;
    }

    // 设置主机模式，发送
    base->I2CR |= ((1 << 5) | (1 << 4));

    // 产生start信号，设置了从机地址后，硬件自动产生
    /*
        I2Cx_I2DR寄存器，bit7-0
    */
    base->I2DR = ((uint32_t)addr << 1) | direction;

    return I2C_STATUS_OK;
}

/* stop信号产生 */
I2C_STATUS i2c_stop(I2C_Type *base)
{
    uint16_t timeout = 0xffff;

    if(NULL == base)
    {
        return I2C_STATUS_ERROR;
    }

    base->I2CR &= ~(0x7 << 3);  // I2Cx_I2CR寄存器相关介绍在init接口中

    while(base->I2SR & (1 << 5))
    {
        -- timeout;
        if(0 == timeout)
        {
            return I2C_STATUS_TIMEOUT;
        }
    }

    return I2C_STATUS_OK;
}

/* restart信号 */
I2C_STATUS i2c_restart(I2C_Type *base, uint8_t addr, I2C_DIRECTION direction)
{
    if(NULL == base)
    {
        return I2C_STATUS_ERROR;
    }

    // 判断是否忙，且工作在从机模式
    if((base->I2SR & (1 << 5)) && (0 == (base->I2CR & (1 << 5))))
    {
        return I2C_STATUS_BUSY;
    }

    base->I2CR |= ((1 << 4) | (1 << 2));

    // 从机地址+读写
    base->I2DR = ((uint32_t)addr << 1) | direction;

    return I2C_STATUS_OK;
}

/* I2C状态检查 */
I2C_STATUS i2c_check_and_clear_error(I2C_Type *base, I2C_STATUS status)
{
    if(NULL == base)
    {
        return I2C_STATUS_ERROR;
    }

    if(status & (1 << 4))
    {
        base->I2SR &= ~(1 << 4);
        base->I2CR &= ~(1 << 7);
        base->I2CR |= 1 << 7;
        return I2C_STATUS_ARBITRATION_LOST;
    }
    else if(status & (1 << 0))
    {
        return I2C_STATUS_NAK;
    }

    return I2C_STATUS_OK;
}

/* 写数据 */
ERR_CODE i2c_write(I2C_Type *base, IN const uint8_t *data, uint32_t dataSize)
{
    if(NULL == base || NULL == data)
    {
        return ERR_BAD_PARAM;
    }

    /* 等待传输完成 */
    while(!(base->I2SR & (1 << 7))) {}

    base->I2SR &= ~(1 << 1);    // 清除中断相关标志位
    base->I2CR |= (1 << 4); // 设置为发送
    
    while(dataSize--)
    {
        base->I2DR = *data++;   // 写入数据
        while(!(base->I2SR & (1 << 1))) {}  // 等待传输完成。这里sdk就是这么写，不知道为什么是这个Bit
        base->I2SR &= ~(1 << 1);    // 设置标志位

        /* 检查ACK */
        if(I2C_STATUS_OK != i2c_check_and_clear_error(base, base->I2SR))
        {
            DBG_ERR("write error occurred");
            break;
        }
    }

    base->I2SR &= ~(1 << 1);

    i2c_stop(base);

    return ERR_NO_ERROR;
}

/* 读数据 */
ERR_CODE i2c_read(I2C_Type *base, OUT uint8_t *data, uint32_t dataSize)
{
    uint8_t dummy = 0;  // 用于假读

    if(NULL == base || NULL == data)
    {
        return ERR_BAD_PARAM;
    }

    /* 等待传输完成 */
    while(!(base->I2SR & (1 << 7))) {}
    base->I2SR &= ~(1 << 1);    // 清除中断相关标志位
    base->I2CR &= ~(0x3 << 3);   // 设置接收，发送ack信号

    if(1 == dataSize)
    {
        base->I2CR |= (1 << 3);     // no ack
    }

    dummy ++;
    dummy = base->I2DR; // 假读

    while(dataSize--)
    {
        while(!(base->I2SR & (1 << 1))) {}  // 等待传输完成。这里sdk就是这么写，不知道为什么是这个Bit
        base->I2SR &= ~(1 << 1);    // 设置标志位

        if(dataSize == 0)   // 数据发送完成
        {
            i2c_stop(base);
        }
        else if(dataSize == 1)
        {
            base->I2CR |= (1 << 3);     // no ack
        }

        *data++ = base->I2DR;
    }

    return ERR_NO_ERROR;
}

/* I2C传输 */
I2C_STATUS i2c_transfer(I2C_Type *base, I2C_TRANSFER *xfer)
{
	unsigned char ret = 0;
	I2C_DIRECTION direction = xfer->direction;	

	base->I2SR &= ~((1 << 1) | (1 << 4));			/* 清除标志位 */

	/* 等待传输完成 */
	while(!((base->I2SR >> 7) & 0X1)){}; 

	/* 如果是读的话，要先发送寄存器地址，所以要先将方向改为写 */
    if ((xfer->subaddressSize > 0) && (xfer->direction == I2C_READ))
    {
        direction = I2C_WRITE;
    }

	ret = i2c_starts(base, xfer->slaveAddress, direction); /* 发送开始信号 */
    if(ret)
    {	
		return ret;
	}

	while(!(base->I2SR & (1 << 1))){};			/* 等待传输完成 */

    ret = i2c_check_and_clear_error(base, base->I2SR);	/* 检查是否出现传输错误 */
    if(ret)
    {
      	i2c_stop(base); 						/* 发送出错，发送停止信号 */
        return ret;
    }

    /* 发送寄存器地址 */
    if(xfer->subaddressSize)
    {
        do
        {
			base->I2SR &= ~(1 << 1);			/* 清除标志位 */
            xfer->subaddressSize--;				/* 地址长度减一 */
			
            base->I2DR =  ((xfer->subaddress) >> (8 * xfer->subaddressSize)); //向I2DR寄存器写入子地址
  
			while(!(base->I2SR & (1 << 1)));  	/* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	i2c_stop(base); 				/* 发送停止信号 */
             	return ret;
            }  
        } while ((xfer->subaddressSize > 0) && (ret == I2C_STATUS_OK));

        if(xfer->direction == I2C_READ) 		/* 读取数据 */
        {
            base->I2SR &= ~(1 << 1);			/* 清除中断挂起位 */
            i2c_restart(base, xfer->slaveAddress, I2C_READ); /* 发送重复开始信号和从机地址 */
    		while(!(base->I2SR & (1 << 1))){};/* 等待传输完成 */

            /* 检查是否有错误发生 */
			ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	ret = I2C_STATUS_ADDRNAK;
                i2c_stop(base); 		/* 发送停止信号 */
                return ret;  
            }
           	          
        }
    }	

    /* 发送数据 */
    if ((xfer->direction == I2C_WRITE) && (xfer->dataSize > 0))
    {
    	i2c_write(base, xfer->data, xfer->dataSize);
	}

    /* 读取数据 */
    if ((xfer->direction == I2C_READ) && (xfer->dataSize > 0))
    {
       	i2c_read(base, xfer->data, xfer->dataSize);
	}
	return 0;	
}