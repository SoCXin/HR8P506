/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  SPI����ģ�����ͷ�ļ�
          ����EEPROM
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "lib_config.h"

#define Slave_Addr  0x5A

/* �������� */
void SPI1Init(void);
void SPIReadData(uint8_t *rbuf, uint8_t n);
void SPIWriteData(uint8_t *wbuf, uint8_t n);

#endif
