/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  uart.h
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/15
*描  述:  UART模块程序（中断收发）头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "lib_config.h"
#include "string.h"

#define HEAD1       0x55        /* 帧头码1 */
#define HEAD2       0xAA        /* 帧头码2 */

#define TAIL1       0x5A        /* 帧尾码1 */
#define TAIL2       0xA5        /* 帧尾码2 */

#define SLAVE_ADDR  0x01        /* 设备地址 */


extern uint8_t g_rxbuf[255];            /* 接收数据缓存 */
extern uint8_t g_rx_length;             /* 接收数据长度 */
extern uint8_t g_txbuf[255];            /* 发送数据缓存 */
extern uint8_t g_tx_length;             /* 发送数据长度 */
extern uint8_t g_rx_time;               /* 字节间隔 */
extern uint8_t g_tx_time;               /* 字节间隔 */
extern volatile uint8_t g_rx_count;             /* 接收字节计数 */
extern volatile uint8_t g_tx_count;             /* 发送字节计数 */
extern volatile uint8_t g_rx_start_flag;        /* 接收起始标志 */
extern volatile uint8_t g_tx_start_flag;        /* 发送起始标志 */
extern volatile uint8_t g_rx_finish_flag;       /* 接收完成标志 */
extern volatile uint8_t g_tx_finish_flag;       /* 发送完成标志 */


void    UARTInit(void);                             /* UART初始化 */
uint8_t UARTRxData(uint8_t *buf);                   /* UART接收数据 */
void    UARTTxData(uint8_t *buf, uint8_t n);        /* UART发送数据 */


#endif
