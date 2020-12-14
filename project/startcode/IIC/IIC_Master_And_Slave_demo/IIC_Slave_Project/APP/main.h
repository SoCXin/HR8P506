/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC主机演示主程序头文件
*备  注:  适用于HRSDK-GDB-ES8P508 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "iic.h"



uint8_t g_wbuf[5];        //写入数据缓存
uint8_t g_rbuf[5];        //读出数据缓存

uint8_t g_txbuf[0xFF];          //发送数据缓存
uint8_t g_tx_length;            //发送数据长度
uint8_t g_tx_count;             //发送字节计数

uint8_t g_rxbuf[0xFF];          //接收数据缓存
uint8_t g_rx_length;            //接收数据长度
uint8_t g_rx_count;             //接收字节计数

uint8_t g_addr;           //片内地址（EEPROM）
uint8_t g_addr_h;         //片内地址高半字节（显示位于g_led_buf[0]）
uint8_t g_addr_l;         //片内地址低半字节（显示位于g_led_buf[1]）

uint8_t g_data;           //读写数据（EEPROM）
uint8_t g_data_h;         //读写数据高半字节（显示位于g_led_buf[2]）
uint8_t g_data_l;         //读写数据低半字节（显示位于g_led_buf[3]）

uint8_t g_led_buf[4];     //显示缓存

uint8_t g_2ms_flag;       //2ms标志
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;      //10ms标志
uint16_t g_10ms_cnt;      //10ms计数

#endif
