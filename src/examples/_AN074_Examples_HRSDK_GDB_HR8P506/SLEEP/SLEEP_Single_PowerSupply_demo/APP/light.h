/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  light.h
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/13
*描  述:  LIGHT指示灯模块程序头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "lib_config.h"

#define LED1_PIN GPIO_Pin_A6
#define LED2_PIN GPIO_Pin_A7
#define LED3_PIN GPIO_Pin_A8
#define LED4_PIN GPIO_Pin_A9

void LightInit(GPIO_Pin Pin);
void LightOn(GPIO_Pin Pin);
void LightOff(GPIO_Pin Pin);

#endif
