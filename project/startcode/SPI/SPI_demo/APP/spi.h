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
#include "systick.h"

/* �������� */
void SPI1Init(void);
void SPI1_Ewen(void);
void SPI1_Ewds(void);
void SPI1ReadData(uint8_t addr, uint8_t *buf, uint8_t n);
void SPI1WriteData(uint8_t addr, uint8_t *buf, uint8_t n);
void SPI1EraseAll(void);

#endif
