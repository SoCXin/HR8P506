/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.h
*作  者:  yuzr
*版  本:  V1.00
*日  期:  2017/10/17
*描  述:  7816演示实验，初始化ESAM模块并复位ESAM，接收ESAM复位应答数据，
                    向ESAM写入测试命令，正确执行命令则LED亮
*备  注:          PB04--IC_IO   PB05--IC_CLK  PB07--IC_RST   PA06--LED
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "lib_config.h"
#include "7816.h"
#include "system_hr8p506.h"
#include "HR8P506.h"


#define  LED_Light   (GPIO->PADATABCR.Word|=(1<<6))  //LED1亮
#define  LED_Dark    (GPIO->PADATABSR.Word|=(1<<6))  //LED1熄灭
#define  LED_PIN     GPIO_Pin_A6

void led_init(void);
