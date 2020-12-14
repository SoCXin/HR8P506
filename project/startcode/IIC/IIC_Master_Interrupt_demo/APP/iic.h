/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  IIC主机模块程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"
#include "systick.h"

extern uint8_t g_txbuf[0xFF];          //发送数据缓存
extern uint8_t g_tx_length;            //发送数据长度
extern uint8_t g_tx_count;             //发送字节计数

extern uint8_t g_rxbuf[0xFF];          //接收数据缓存
extern uint8_t g_rx_length;            //接收数据长度
extern uint8_t g_rx_count;             //接收字节计数

void IIC0_MasterInit(void);
uint8_t IIC0_ReadByte(uint8_t slave_addr, uint8_t memory_addr);
ErrorStatus IIC0_WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf);
void IIC0_MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
void IIC0_MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
ErrorStatus IIC0_MasterErasePage(uint8_t slave_addr, uint8_t memory_addr);

#endif
