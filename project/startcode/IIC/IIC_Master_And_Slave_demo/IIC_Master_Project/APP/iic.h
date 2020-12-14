/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC从机模块头文件
*备  注:  适用于HRSDK-GDB-ES8P508 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"

#define SLAVE_ADDR  0x5A    //从机地址

void IICMasterInit(void);
uint8_t IICReadByte(uint8_t slave_addr);
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf);
void IICReadBuf(uint8_t slave_addr, char *buf, char size);
ErrorStatus IICWriteBuf(uint8_t slave_addr, char *buf, char size);

#endif
