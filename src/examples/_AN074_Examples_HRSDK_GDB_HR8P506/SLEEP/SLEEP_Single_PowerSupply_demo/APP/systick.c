/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  systick.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/13
*描  述:  系统滴答模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "systick.h"

__IO uint32_t TimingDelay;

/*********************************************************
函数名: void User_SysTickInit(void)
描  述: 系统滴答初始化：100us
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void User_SysTickInit(void)
{
    SYSTICK_InitStruType x;

    x.SysTick_Value = SystemCoreClock / 10000;
    x.SysTick_ClkSource = SysTick_ClkS_Cpu;
    x.SysTick_ITEnable = Enable;
    SysTick_Init(&x);

    SysTick_Disable();
}

/*********************************************************
函数名: void Delay_100us(__IO uint32_t nTime)
描  述: 系统滴答100us定时
输入值: 定时100us个数
输出值: 无
返回值: 无
**********************************************************/
void Delay_100us(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    SysTick_Enable();

    while (TimingDelay != 0);

    SysTick_Disable();
}

/*********************************************************
函数名: void TimingDelay_Decrement(void)
描  述: 系统滴答中断调用
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0)
        TimingDelay --;
}
