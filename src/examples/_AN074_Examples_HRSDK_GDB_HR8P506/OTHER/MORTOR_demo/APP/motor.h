/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  motor.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/07/13
*描  述:  步进电机驱动头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "lib_gpio.h"

void MotorInit(void);
void MotorWrite(uint8_t data);

#endif
