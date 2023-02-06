/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/13
*描  述:  外部端口中断配置程序头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "lib_config.h"
void GPIOInit(void);
void PINTx_Init(void);
void KINTx_Init(void);

#endif

