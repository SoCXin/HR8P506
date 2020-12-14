/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  SPI主机模块程序头文件
          访问EEPROM
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "lib_config.h"
#include "systick.h"

/* 函数声明 */
void SPI1Init(void);
void SPI1_Ewen(void);
void SPI1_Ewds(void);
void SPI1ReadData(uint8_t addr, uint8_t *buf, uint8_t n);
void SPI1WriteData(uint8_t addr, uint8_t *buf, uint8_t n);
void SPI1EraseAll(void);

#endif
