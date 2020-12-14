/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC������ʾ������ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "iic.h"



uint8_t g_wbuf[5];        //д�����ݻ���
uint8_t g_rbuf[5];        //�������ݻ���

uint8_t g_txbuf[0xFF];          //�������ݻ���
uint8_t g_tx_length;            //�������ݳ���
uint8_t g_tx_count;             //�����ֽڼ���

uint8_t g_rxbuf[0xFF];          //�������ݻ���
uint8_t g_rx_length;            //�������ݳ���
uint8_t g_rx_count;             //�����ֽڼ���

uint8_t g_addr;           //Ƭ�ڵ�ַ��EEPROM��
uint8_t g_addr_h;         //Ƭ�ڵ�ַ�߰��ֽڣ���ʾλ��g_led_buf[0]��
uint8_t g_addr_l;         //Ƭ�ڵ�ַ�Ͱ��ֽڣ���ʾλ��g_led_buf[1]��

uint8_t g_data;           //��д���ݣ�EEPROM��
uint8_t g_data_h;         //��д���ݸ߰��ֽڣ���ʾλ��g_led_buf[2]��
uint8_t g_data_l;         //��д���ݵͰ��ֽڣ���ʾλ��g_led_buf[3]��

uint8_t g_led_buf[4];     //��ʾ����

uint8_t g_2ms_flag;       //2ms��־
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;      //10ms��־
uint16_t g_10ms_cnt;      //10ms����

#endif
