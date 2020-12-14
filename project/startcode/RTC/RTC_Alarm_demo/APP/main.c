/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  RTCģ������
            �գ��ֱܷ���һ���жϣ����жϾ���������LD2-LD4������
            �������ж�δ��������LD2-LD4��˸��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    SCU_OpenXTAL();

    User_SysTickInit();
    LightInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    g_day_flag = 0;
    g_week_flag = 0;

    RTC_Init(RTC_LRC, RTC_HOUR24);

    RTC_WriteHour(15, 0);
    RTC_WriteMinute(24);
    RTC_WriteSecond(58);

    RTC_WriteDayAlarmHour(15, 0);
    RTC_WriteDayAlarmMinute(25);
    RTC_InterruptEnable(RTC_Interrupt_Source_DayALE);
    Delay_100us(30000);

    RTC_WriteWeek(4);
    RTC_WriteMonth(7);
    RTC_WriteDay(6);
    RTC_WriteHour(16, 0);
    RTC_WriteMinute(24);
    RTC_WriteSecond(58);

    RTC_WriteWeekAlarmWeek(4);
    RTC_WriteWeekAlarmHour(16, 0);
    RTC_WriteWeekAlarmMinute(25);
    RTC_InterruptEnable(RTC_Interrupt_Source_WeekALE);
    Delay_100us(30000);

    while (1)
    {
        if (g_day_flag == 1 && g_week_flag == 1)
        {
            GPIO_WriteBit(GPIO_Pin_A7, 0);
            GPIO_WriteBit(GPIO_Pin_A8, 0);
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        }
        else
        {
            GPIO_WriteBit(GPIO_Pin_A7, 0);
            GPIO_WriteBit(GPIO_Pin_A8, 0);
            GPIO_WriteBit(GPIO_Pin_A9, 0);
            Delay_100us(5000);

            GPIO_WriteBit(GPIO_Pin_A7, 1);
            GPIO_WriteBit(GPIO_Pin_A8, 1);
            GPIO_WriteBit(GPIO_Pin_A9, 1);
            Delay_100us(5000);
        }

    }
}
