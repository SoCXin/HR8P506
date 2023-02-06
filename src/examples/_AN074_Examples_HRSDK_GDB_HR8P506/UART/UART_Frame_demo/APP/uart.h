/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������ж��շ���ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "lib_config.h"

#define HEAD1       0x55        //֡ͷ��1
#define HEAD2       0xAA        //֡ͷ��2

#define TAIL1       0x5A        //֡β��1
#define TAIL2       0xA5        //֡β��2

#define SLAVE_ADDR      0x01        //�豸��ַ

extern uint8_t flag;


void UARTInit(void);                //UART��ʼ��
uint8_t UARTRxData(uint8_t *buf, uint8_t n);    //UART��������
void UARTTxData(uint8_t *buf, uint8_t n);       //UART��������

#endif
