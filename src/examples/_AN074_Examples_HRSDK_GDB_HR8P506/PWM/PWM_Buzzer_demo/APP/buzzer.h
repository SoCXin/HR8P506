/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  buzzer.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  蜂鸣器模块API头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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
