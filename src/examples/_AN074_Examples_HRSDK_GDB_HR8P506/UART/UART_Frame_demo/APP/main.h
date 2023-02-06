/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:    main.h
*��  ��:    Liut
*��  ��:    V1.01
*��  ��:    2017/06/29
*��  ��:    UART��ʾ������ͷ�ļ�
*��  ע:    
            ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "HR8P506.h"
#include "uart.h"
#include "led.h"
#include "timer.h"
#include "systick.h"
#include "lib_config.h"
#include "system_HR8P506.h"

uint8_t g_2ms_flag;
uint8_t g_2ms_cnt;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint8_t g_500ms_flag;
uint8_t g_500ms_cnt;

uint8_t g_txbuf[0xFF];            //�������ݻ���
uint8_t g_tx_length;            //�������ݳ���
uint8_t g_tx_count;             //�����ֽڼ���

uint8_t g_rxbuf[0xFF];            //�������ݻ���
uint8_t g_rx_length;            //�������ݳ���
uint8_t g_rx_count;             //�����ֽڼ���
uint8_t g_rx_time;              //���ռ�ʱ
uint8_t g_rx_finish_flag;       //������ɱ�־
uint8_t g_rx_start_flag;        //������ʼ��־

uint8_t g_data1;                //��������1
uint8_t g_data1_h;              //��������1�߰��ֽڣ���ʾλ��g_led_buf[0]��
uint8_t g_data1_l;              //��������1�Ͱ��ֽڣ���ʾλ��g_led_buf[1]��

uint8_t g_data2;                //��������2
uint8_t g_data2_h;              //��������2�߰��ֽڣ���ʾλ��g_led_buf[2]��
uint8_t g_data2_l;              //��������2�Ͱ��ֽڣ���ʾλ��g_led_buf[3]��

uint8_t g_led_buf[4];           //��ʾ����

#endif
