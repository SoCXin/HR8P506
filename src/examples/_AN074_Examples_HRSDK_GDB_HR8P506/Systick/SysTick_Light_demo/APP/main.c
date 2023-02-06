/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  systick示例程序
        Light灯闪烁，LD1，LD3和LD2，LD4间隔200ms分别闪烁，间隔时间使用SysTick定时器
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();

    while (1)
    {
        GPIO_WriteBit(GPIO_Pin_A6, 1);
        GPIO_WriteBit(GPIO_Pin_A7, 0);
        GPIO_WriteBit(GPIO_Pin_A8, 1);
        GPIO_WriteBit(GPIO_Pin_A9, 0);
        Delay_100us(2000);

        GPIO_WriteBit(GPIO_Pin_A6, 0);
        GPIO_WriteBit(GPIO_Pin_A7, 1);
        GPIO_WriteBit(GPIO_Pin_A8, 0);
        GPIO_WriteBit(GPIO_Pin_A9, 1);
        Delay_100us(2000);
    }
}
