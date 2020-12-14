/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.02
*日  期:  2017/06/29
*描  述:  PWM示例程序
            在PA6、PA7引脚输出同步PWM波形
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);
    SystemInit();
    DeviceClockAllEnable();

    T16NxInit();

    while (1)
    {
    }
}

