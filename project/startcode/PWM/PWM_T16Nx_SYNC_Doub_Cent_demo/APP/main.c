/*********************************************************
*Copyright (C), 2019, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2019/11/29
*描  述:  PWM示例程序
                          SCU同步启动两T16N，PA6、PA7、PA8、PA9输出四路同步中心对齐PWM波
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

    while (1);
}
