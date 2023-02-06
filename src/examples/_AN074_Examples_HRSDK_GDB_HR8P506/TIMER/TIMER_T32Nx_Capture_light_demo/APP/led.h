/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  led.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LED显示程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __LED_H__
#define __LED_H__

#include "lib_config.h"
#include "lib_gpio.h"
#include "lib_led.h"

#define CODEMAX 16
#define COMMAX 4

void LEDInit(void);
int32_t LEDDisplayData(uint8_t com, uint8_t dat);
void LEDDisplaySeg(uint8_t seg);
int32_t DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data);

#endif

