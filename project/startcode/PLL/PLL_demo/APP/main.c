/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  PLL例程
             PLL倍频到48M后，定时闪烁LD1指示灯
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{

    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);    //PLL使能，倍频到48M（可关闭打开分别观察指示灯闪烁差异 ,或看PA6波形更直观）
    SCU->SCLKEN0.CLKFLT_BY = 0x55; //PLL倍频到48M时，需要旁路时钟滤波器CLKFLT；否则注释此行
    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    T16N3Init();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {

        GPIO->PADATABCR.Word = 0x00000040; //PA6清0
        GPIO->PADATABSR.Word = 0x00000040; //PA6置1
//        GPIO->PADATABRR.Word = 0x00000040; //PA6取反

    }
}

