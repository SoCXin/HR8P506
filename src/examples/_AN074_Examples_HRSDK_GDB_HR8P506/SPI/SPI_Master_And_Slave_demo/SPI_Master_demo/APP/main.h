/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/20
*描  述:  SPI主从通信主程序头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "system_HR8P506.h"
#include "string.h"
#include "spi.h"
#include "systick.h"

extern uint8_t g_wbuf[8];
extern uint8_t g_rbuf[16];
extern uint8_t g_rbufamount;
extern uint8_t g_wbufamount;


#endif

