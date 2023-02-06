/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  LIUT
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  32位定时器例程
            TN32N0定时，定时到闪烁LD1-LD4指示灯
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码
          所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    T32NxInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1);
}
