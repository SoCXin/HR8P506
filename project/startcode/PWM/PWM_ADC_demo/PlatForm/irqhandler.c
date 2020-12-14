#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_timer.h"
#include "lib_config.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1);
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{

}



/*********************************************************
函数名: void T16N0_IRQHandler(void)
描  述: T16N0中断处理函数 1000us
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N0_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N0, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N0, T16Nx_IT_MAT0);
    }
}

extern uint16_t ad_temp;
/*********************************************************
函数名: void ADC_IRQHandler(void)
描  述: ADC中断处理
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void ADC_IRQHandler()
{
    if (ADC_GetIFStatus(ADC_IF) == SET)
    {
        while (ADC_GetIFStatus(ADC_IF) == RESET);

        ad_temp = ADC_GetConvValue();
    }

    ADC_ClearIFStatus(ADC_IF);
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

        g_10ms_cnt++;

        if (g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }

        g_500ms_cnt++;

        if (g_500ms_cnt >= 250)
        {
            g_500ms_cnt = 0;
            g_500ms_flag = 1;
        }
    }

    return;
}

