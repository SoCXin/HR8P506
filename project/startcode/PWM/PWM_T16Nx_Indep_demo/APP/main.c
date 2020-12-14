/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.02
*日  期:  2017/06/29
*描  述:  16位调制器示例程序
            在PB1、PA7引脚输出占空比1:2，周期5ms的PWM波形，PA6输出不同占空比的PWM波形
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    T16NxInit();

    while (1)
    {
    }
}

