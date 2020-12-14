/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  IIC������ʾ������ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "HR8P506.h"
#include "key.h"
#include "iic.h"
#include "led.h"
#include "timer.h"
#include "systick.h"
#include "lib_config.h"
#include "system_HR8P506.h"
#include "string.h"

#define    SLAVE_ADDR  0xA0        //�ӻ�EEPROM��ַ��

uint8_t g_txbuf[0xFF];          //�������ݻ���
uint8_t g_tx_length;            //�������ݳ���
uint8_t g_tx_count;             //�����ֽڼ���

uint8_t g_rxbuf[0xFF];          //�������ݻ���
uint8_t g_rx_length;            //�������ݳ���
uint8_t g_rx_count;             //�����ֽڼ���

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

uint8_t addr;         //Ƭ�ڵ�ַ
uint8_t addr_h;       //Ƭ�ڵ�ַ�߰��ֽڣ���ʾλ��led_buf[0]��
uint8_t addr_l;       //Ƭ�ڵ�ַ�Ͱ��ֽڣ���ʾλ��led_buf[1]��

uint8_t data;         //��д����
uint8_t data_h;       //��д���ݸ߰��ֽڣ���ʾλ��led_buf[2]��
uint8_t data_l;       //��д���ݵͰ��ֽڣ���ʾλ��led_buf[3]��

uint8_t g_key_cmd;
uint8_t flag;
uint8_t com;
uint8_t g_led_buf[4];    //��ʾ����

#endif

