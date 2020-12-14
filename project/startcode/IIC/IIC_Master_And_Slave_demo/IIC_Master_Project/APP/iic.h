/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC�ӻ�ģ��ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"

#define SLAVE_ADDR  0x5A    //�ӻ���ַ

void IICMasterInit(void);
uint8_t IICReadByte(uint8_t slave_addr);
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf);
void IICReadBuf(uint8_t slave_addr, char *buf, char size);
ErrorStatus IICWriteBuf(uint8_t slave_addr, char *buf, char size);

#endif
