#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_config.h"

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
    //TimingDelay_Decrement();
}

/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);
        g_2ms_flag = 1;

        g_1s_cnt++;

        if (g_1s_cnt >= 500)
        {
            g_1s_cnt = 0;
            g_1s_flag = 1;
        }
    }

    return;
}

/*********************************************************
函数名: void Interrupt_KINT_Handler(void)
描  述: 按键中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void KINT_IRQHandler(void)
{
    if (KINT_GetITFlag(GPIO_Pin_B9) != RESET)
    {
        KINT_ClearITFlag(GPIO_Pin_B9);      // 清除按键中断标志位
        g_key_flag = 1;
    }
}


