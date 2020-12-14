#include "irqhandler.h"
#include "lib_wdt.h"
#include "systick.h"
#include "lib_rtc.h"

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
    TimingDelay_Decrement();
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

uint32_t SecondCount = 0;
uint32_t MinuteCount = 0;
uint32_t HourCount = 0;
uint32_t DayCount = 0;
uint32_t MonthCount = 0;
/*********************************************************
������: void RTC_IRQHandler(void)
��  ��: ʵʱʱ���жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void RTC_IRQHandler(void)
{
    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Second) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_Second) != RESET)   //����ж�Դʱ����ͬʱ�ж�IE��IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Second);    //���жϱ�ʶ
        g_sec_flag = 1;

        SecondCount++;

        if ((SecondCount & 0x01) == 0x01)
            GPIO_WriteBit(GPIO_Pin_A6, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A6, 1);
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Minute) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_Minute) != RESET)   //����ж�Դʱ����ͬʱ�ж�IE��IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Minute);    //���жϱ�ʶ
        g_min_flag = 1;
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Hour) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_Hour) != RESET) //����ж�Դʱ����ͬʱ�ж�IE��IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Hour);    //���жϱ�ʶ
        g_hour_flag = 1;
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Day) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_Day) != RESET)  //����ж�Դʱ����ͬʱ�ж�IE��IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Day);    //���жϱ�ʶ
        g_day_flag = 1;
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Month) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_Month) != RESET)    //����ж�Դʱ����ͬʱ�ж�IE��IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Month);    //���жϱ�ʶ
        g_month_flag = 1;
    }
}

