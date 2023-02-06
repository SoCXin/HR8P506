/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/21
*描  述:  sleep示例程序
          程序运行如下：
          1. 上电完成初始化操作后，LED1亮3S灭1S
          2. 进入主循环，LED1亮1S灭1S，进入深睡眠
          唤醒源：
          1. PINT
          2. KINT
          连线：
          PINT：PA1
          KINT：PA3
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();
    User_SysTickInit();
    GPIOInit(); //端口输出固定电平，以降低功耗
    
    /* 配置唤醒源PINT、KINT及LED1，初始化完成后LED亮3S灭1S */
    KINTx_Init();
    PINTx_Init();

    LightInit(LED1_PIN);
    LightOn(LED1_PIN);
    Delay_100us(30000);
    LightOff(LED1_PIN);
    Delay_100us(10000);

    while (1)
    {
        LightOn(LED1_PIN);
        Delay_100us(10000);
        LightOff(LED1_PIN);
        Delay_100us(10000);
        /* 深睡 */
        deep_sleep();
    }
}
