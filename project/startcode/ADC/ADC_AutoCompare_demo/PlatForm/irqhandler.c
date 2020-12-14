#include "irqhandler.h"
#include "lib_config.h"
#include "lib_wdt.h"

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
������: void T16N3_IRQHandler(void)
��  ��: T16N3��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
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

/*********************************************************
������: void ADC_IRQHandler(void)
��  ��: ADC�жϴ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void ADC_IRQHandler()
{
    if (ADC_GetIFStatus(ADC_IF_ACPOVER) == SET)
    {
//      meanvalue = ADC_GetACPMeanValue();
        ADC_ClearIFStatus(ADC_IF_ACPOVER);
    }

    if (ADC_GetIFStatus(ADC_IF_ACPMIN) == SET)
    {
//      meanvalue = ADC_GetACPMeanValue();
        ADC_ClearIFStatus(ADC_IF_ACPMIN);
    }

    if (ADC_GetIFStatus(ADC_IF_ACPMAX) == SET)
    {
        meanvalue = ADC_GetACPMeanValue();
        ADC_ClearIFStatus(ADC_IF_ACPMAX);
    }

    ADC_ClearIFStatus(ADC_IF);
}


