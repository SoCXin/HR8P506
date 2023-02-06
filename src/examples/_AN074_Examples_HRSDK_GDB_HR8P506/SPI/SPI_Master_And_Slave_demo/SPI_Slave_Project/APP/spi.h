/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/09
*描  述:  SPI从机模块程序头文件
*备  注:
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "lib_config.h"


#define Slave_Addr  0x5A

/* 函数声明 */
void SPI1Init(void);
void SPIReadData(uint8_t *rbuf, uint8_t n);
void SPIWriteData(uint8_t *wbuf, uint8_t n);

#endif
