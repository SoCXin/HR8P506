/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  IIC����ģ�����ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"
#include "systick.h"

extern uint8_t g_txbuf[0xFF];          //�������ݻ���
extern uint8_t g_tx_length;            //�������ݳ���
extern uint8_t g_tx_count;             //�����ֽڼ���

extern uint8_t g_rxbuf[0xFF];          //�������ݻ���
extern uint8_t g_rx_length;            //�������ݳ���
extern uint8_t g_rx_count;             //�����ֽڼ���

void IIC0_MasterInit(void);
uint8_t IIC0_ReadByte(uint8_t slave_addr, uint8_t memory_addr);
ErrorStatus IIC0_WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf);
void IIC0_MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
void IIC0_MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
ErrorStatus IIC0_MasterErasePage(uint8_t slave_addr, uint8_t memory_addr);

#endif
