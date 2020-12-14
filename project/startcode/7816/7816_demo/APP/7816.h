/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  7816.h
*��  ��:  yuzr
*��  ��:  V1.00
*��  ��:  2017/10/11
*��  ��:  7816����ģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __7816_H__
#define __7816_H__

#include "lib_config.h"

#define  SendByte_Size  20


#define  E0CK0_PIN   GPIO_Pin_B5
#define  E0IO0_PIN   GPIO_Pin_B4
#define  E0RST_PIN   GPIO_Pin_B7

#define  ESAM_RST_L  (GPIO->PBDATABCR.Word|=(1<<7))
#define  ESAM_RST_H  (GPIO->PBDATABSR.Word|=(1<<7))



/*��������*/
void User_7816Init(void);
uint8_t Get_7816_Char(uint8_t *Data);
uint8_t  Snd_7816_Byte(uint8_t Data);
uint8_t ResetRec(uint8_t *RxBuf);
uint8_t  Instruction_Test(void);
uint8_t Random_Test(uint8_t *data);
void DLY_X100us(uint16_t Count_x100us);

#endif
