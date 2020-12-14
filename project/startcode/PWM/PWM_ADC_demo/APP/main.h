/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô���
          �������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "system_HR8P506.h"
#include "lib_config.h"
#include "lib_timer.h"
#include "lib_gpio.h"
#include "lib_scu.h"
#include "timer.h"
#include "adc.h"
#include "led.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

#endif
