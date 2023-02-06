/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  IIC从机模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"

#define SLAVE_ADDR  0x2D << 1

void I2C0_SlaveInit(void);


#endif
