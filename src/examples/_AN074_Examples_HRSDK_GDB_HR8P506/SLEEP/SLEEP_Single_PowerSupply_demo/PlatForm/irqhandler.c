#include "irqhandler.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1)
    {
    }
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}

/*********************************************************
函数名: void PINT1_IRQHandler(void)
描  述: 端口中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void PINT1_IRQHandler(void)
{
    if (PINT_GetITFlag(GPIO_Pin_A1) == SET)
    {
        PINT_ClearITFlag(GPIO_Pin_A1);
    }
}

/*********************************************************
函数名: void KINT_IRQHandler(void)
描  述: 按键中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void KINT_IRQHandler(void)
{
    if (KINT_GetITFlag(GPIO_Pin_A3) == SET)
    {
        KINT_ClearITFlag(GPIO_Pin_A3);
    }
}



