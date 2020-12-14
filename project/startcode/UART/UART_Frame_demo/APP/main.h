/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:    main.h
*作  者:    Liut
*版  本:    V1.01
*日  期:    2017/06/29
*描  述:    UART演示主程序头文件
*备  注:    
            本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "HR8P506.h"
#include "uart.h"
#include "led.h"
#include "timer.h"
#include "systick.h"
#include "lib_config.h"
#include "system_HR8P506.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

uint8_t g_txbuf[0xFF];            //发送数据缓存
uint8_t g_tx_length;            //发送数据长度
uint8_t g_tx_count;             //发送字节计数

uint8_t g_rxbuf[0xFF];            //接收数据缓存
uint8_t g_rx_length;            //接收数据长度
uint8_t g_rx_count;             //接收字节计数
uint8_t g_rx_time;              //接收计时
uint8_t g_rx_finish_flag;       //接收完成标志
uint8_t g_rx_start_flag;        //接收起始标志

uint8_t g_data1;                //接收数据1
uint8_t g_data1_h;              //接收数据1高半字节（显示位于g_led_buf[0]）
uint8_t g_data1_l;              //接收数据1低半字节（显示位于g_led_buf[1]）

uint8_t g_data2;                //接收数据2
uint8_t g_data2_h;              //接收数据2高半字节（显示位于g_led_buf[2]）
uint8_t g_data2_l;              //接收数据2低半字节（显示位于g_led_buf[3]）

uint8_t g_led_buf[4];           //显示缓存

#endif
