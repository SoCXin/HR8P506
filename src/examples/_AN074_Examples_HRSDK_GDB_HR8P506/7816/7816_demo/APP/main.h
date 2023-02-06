/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.h
*��  ��:  yuzr
*��  ��:  V1.00
*��  ��:  2017/10/17
*��  ��:  7816��ʾʵ�飬��ʼ��ESAMģ�鲢��λESAM������ESAM��λӦ�����ݣ�
                    ��ESAMд����������ȷִ��������LED��
*��  ע:          PB04--IC_IO   PB05--IC_CLK  PB07--IC_RST   PA06--LED
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "lib_config.h"
#include "7816.h"
#include "system_hr8p506.h"
#include "HR8P506.h"


#define  LED_Light   (GPIO->PADATABCR.Word|=(1<<6))  //LED1��
#define  LED_Dark    (GPIO->PADATABSR.Word|=(1<<6))  //LED1Ϩ��
#define  LED_PIN     GPIO_Pin_A6

void led_init(void);
