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

void I2C0_SlaveInit(void);
void I2C0_Init(void);

#endif
