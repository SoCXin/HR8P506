/*********************************************************
 *Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ���:  RTC.h
 *��  ��:  yuzr
 *��  ��:  V1.00
 *��  ��:  2017/10/23
 *��  ��:  �û�RTCģ�����ͷ�ļ�
 *��  ע:  
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
