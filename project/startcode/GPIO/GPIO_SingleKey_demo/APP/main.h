/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LED演示主程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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
