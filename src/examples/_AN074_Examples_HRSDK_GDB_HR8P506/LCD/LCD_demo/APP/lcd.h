/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  lcd.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LCDģ�����ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __LCD_H__
#define __LCD_H__

#include "lib_config.h"
#include "lib_gpio.h"
#include "lib_lcd.h"

void LCDInit(void);     //LCD��ʾ��ʼ���ӳ���
int32_t LCDAdjust(LCD_TYPE_BVS BVS_Sel, LCD_TYPE_FLIK Flick, uint8_t On_Time, uint8_t Off_Time, LCD_TYPE_RS Rsel, LCD_TYPE_RT Rtime);
int32_t LCDDisplayData(uint8_t high, uint8_t low, uint8_t colon);


#endif

