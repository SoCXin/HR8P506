/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  led.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LED��ʾ����ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __LED_H__
#define __LED_H__

#include "lib_config.h"
#include "lib_gpio.h"
#include "lib_led.h"

#define CODEMAX 16
#define COMMAX 4

void LEDInit(void);
int32_t LEDDisplayData(uint8_t com, uint8_t dat);
void LEDDisplaySeg(uint8_t seg);
int32_t DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data);

#endif

