/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  lcd.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LCD模块程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __LCD_H__
#define __LCD_H__

#include "lib_config.h"
#include "lib_gpio.h"
#include "lib_lcd.h"

void LCDInit(void);     //LCD显示初始化子程序
int32_t LCDAdjust(LCD_TYPE_BVS BVS_Sel, LCD_TYPE_FLIK Flick, uint8_t On_Time, uint8_t Off_Time, LCD_TYPE_RS Rsel, LCD_TYPE_RT Rtime);
int32_t LCDDisplayData(uint8_t high, uint8_t low, uint8_t colon);


#endif

