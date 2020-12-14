/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  adc.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  ADC模块程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "lib_config.h"

void ADCInit(void);
uint16_t ADCRead(void);
void ADCACPConfig(void);

#endif
