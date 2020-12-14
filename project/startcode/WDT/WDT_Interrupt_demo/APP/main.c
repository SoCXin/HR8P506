/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  看门狗示例程序
            看门狗定时2s，在看门狗中断函数中，喂狗则不复位，LD1-LD4闪烁正常，不喂狗则复位，LD1-LD4不正常闪烁
            注：中断一定将配置字里面的WDTINTEN使能！！！！！！！！
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

/*********************************************************
函数名: int main(void)
描  述: 主函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
int main(void)
{

    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_32M, Enable);    //PLL??,???48M(????????????????
    SystemInit();
    DeviceClockAllEnable();
    User_SysTickInit();
    LightInit();
    WdtInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {
        GPIO_WriteBit(GPIO_Pin_A6, 1);
        GPIO_WriteBit(GPIO_Pin_A7, 1);
        GPIO_WriteBit(GPIO_Pin_A8, 1);
        GPIO_WriteBit(GPIO_Pin_A9, 1);
        Delay_100us(2000);

        GPIO_WriteBit(GPIO_Pin_A6, 0);
        GPIO_WriteBit(GPIO_Pin_A7, 0);
        GPIO_WriteBit(GPIO_Pin_A8, 0);
        GPIO_WriteBit(GPIO_Pin_A9, 0);
        Delay_100us(2000);
    }
}
