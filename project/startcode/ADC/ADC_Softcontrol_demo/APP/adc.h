/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  adc.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ADCģ�����ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "lib_config.h"

extern uint16_t meanvalue;
extern uint8_t acp_flag;
void ADCInit(void);
uint16_t ADCRead(void);

#endif
