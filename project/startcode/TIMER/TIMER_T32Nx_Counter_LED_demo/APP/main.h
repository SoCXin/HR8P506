/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  32λ������ʾ������ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô���
          �������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "system_HR8P506.h"
#include "lib_timer.h"
#include "lib_gpio.h"
#include "lib_scu.h"
#include "lib_scs.h"
#include "led.h"
#include "light.h"
#include "timer.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;
uint8_t g_1s_flag;
uint32_t g_1s_cnt;

#endif
