/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  实时时钟示例程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码
          所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "system_HR8P506.h"
#include "lib_config.h"
#include "lib_rtc.h"
#include "led.h"
#include "light.h"
#include "systick.h"
#include "timer.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

#endif
