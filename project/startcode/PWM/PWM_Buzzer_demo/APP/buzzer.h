/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  buzzer.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ������ģ��APIͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "system_HR8P506.h"
#include "lib_timer.h"
#include "lib_gpio.h"
#include "type.h"
#include "systick.h"

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_ChangeFrequency(uint16_t NewFrequency);

void PlayMusic(const uint8_t *sheet);
void PlayTone(void);

#endif
