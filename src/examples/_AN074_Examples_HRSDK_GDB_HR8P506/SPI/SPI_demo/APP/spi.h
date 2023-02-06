/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/20
*描  述:  SPI主机模块程序头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "lib_config.h"
#include "string.h"

/* 定义宏名：SPI通信管脚 */
#define SPI_NSS     GPIO_Pin_A27
#define SPI_SCK     GPIO_Pin_A26
#define SPI_MISO    GPIO_Pin_A25
#define SPI_MOSI    GPIO_Pin_A24

/* 外部变量 */
extern uint8_t g_wbuf[260];
extern uint8_t g_rbuf[260];
extern volatile uint8_t rbufIndex;
extern volatile uint8_t wbufIndex;
extern volatile uint8_t g_rbufamount;
extern volatile uint8_t g_wbufamount;

/* 函数声明 */
void SPI1Init(void);

#endif
