/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.h
*作  者:  yuzr
*版  本:  V1.00
*日  期:  2017/10/24
*描  述:  RTC误差补偿demo,本例程实现RTC外部晶振的误差补偿。
                    选择RTC0引脚1Hz输出，测取RTC误差，由误差计算出补偿值，
                    再进行误差补偿。
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "lib_config.h"
#include "system_HR8P506.h"
#include "HR8P506.h"
#include "RTC.h"



