/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  内部Flash演示主程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "HR8P506.h"
#include "key.h"
#include "spi.h"
#include "led.h"
#include "timer.h"
#include "systick.h"
#include "lib_config.h"
#include "system_hr8p506.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

uint8_t addr;         //片内地址
uint8_t addr_h;       //片内地址高半字节（显示位于led_buf[0]）
uint8_t addr_l;       //片内地址低半字节（显示位于led_buf[1]）

uint8_t data;         //读写数据
uint8_t data_h;       //读写数据高半字节（显示位于led_buf[2]）
uint8_t data_l;       //读写数据低半字节（显示位于led_buf[3]）

uint8_t g_key_cmd;
uint8_t flag;
uint8_t com;

uint8_t g_led_buf[4];

#endif

