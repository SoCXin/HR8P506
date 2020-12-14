/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LED��ʾ������ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef _MAIN_H
#define _MAIN_H

#include "system_HR8P506.h"
#include "lib_config.h"
#include "HR8P506.h"
#include "led.h"
#include "timer.h"
#include "key.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_1s_flag;
uint32_t g_1s_cnt;

uint8_t g_key_flag;

#endif
