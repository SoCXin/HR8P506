/*********************************************************
 *Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名:  RTC.h
 *作  者:  yuzr
 *版  本:  V1.00
 *日  期:  2017/10/23
 *描  述:  用户RTC模块程序头文件
 *备  注:  
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#ifndef  _RTC_H_
#define  _RTC_H_

#include "lib_config.h"
#include "HR8P506.h"



#define  RTC0_PIN    GPIO_Pin_A21

#define  RTC0_Enable()  (RTC->CALC.CLKC = 1)  //PA17
#define  RTC0_Disable() (RTC->CALC.CLKC = 0)    //PA17


void Error_Offset(uint8_t error);
void MyRTC_Init(void);
#endif
