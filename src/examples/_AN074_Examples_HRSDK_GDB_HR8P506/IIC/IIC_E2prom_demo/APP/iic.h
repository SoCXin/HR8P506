/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  IIC主机模块头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"


/******函数原型*************/
void IICMasterInit(void);
uint8_t IICReadByte(uint8_t slave_addr);
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf);
void IICReadBuf(uint8_t slave_addr, uint8_t *buf, uint8_t size);
ErrorStatus IICWriteBuf(uint8_t slave_addr, uint8_t *buf, uint8_t size);

#endif
