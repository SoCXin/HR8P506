/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  RTCģ������
            RTC���1s����һ���жϣ�������LD1������ʱ������ż����ʱ�رգ�
            �£��գ�ʱ���֣���ֱ���һ���жϣ����жϾ���������LD2-LD4������
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

    g_sec_flag = 0;
    g_min_flag = 0;
    g_hour_flag = 0;
    g_day_flag = 0;
    g_month_flag = 0;

    RTC_Init(RTC_LRC, RTC_HOUR24);

    RTC_WriteSecond(30);
    RTC_InterruptEnable(RTC_Interrupt_Source_Second);
    Delay_100us(30000);

    RTC_WriteMinute(30);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Minute);
    Delay_100us(30000);

    RTC_WriteHour(14, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Hour);
    Delay_100us(30000);

    RTC_WriteDay(25);
    RTC_WriteHour(23, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Day);
    Delay_100us(30000);

    RTC_WriteMonth(6);
    RTC_WriteDay(30);
    RTC_WriteHour(23, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Month);
    Delay_100us(30000);

    while (1)
    {
        if (g_sec_flag == 1
                && g_min_flag == 1
                && g_hour_flag == 1
                && g_day_flag == 1
                && g_month_flag == 1)
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
