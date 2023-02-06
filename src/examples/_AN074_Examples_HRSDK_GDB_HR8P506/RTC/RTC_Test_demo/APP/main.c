/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  RTCģ������ (������CFG_OSCMDһ��ѡ��LPģʽ��������)
            RTCдһ���̶�ʱ�䣬����ʱ���Ƿ���д��ʱ��һ�£���һ����LD1-LD4�Ƽ����˸��һ����LD1-LD4������
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

/*********************************************************
������: uint32_t RTC_Test(void)
��  ��: ʵʱʱ��API����
����ֵ: ��
���ֵ: ��
����ֵ: SUCCESS: ���Գɹ�
        ERROR: ����ʧ��
**********************************************************/
ErrorStatus RTC_Test(void)
{
    uint32_t sec, min, hour, day, month, year, week;
    uint32_t meridiem, mode;
    uint32_t wa_min, wa_hour, wa_week;
    uint32_t da_min, da_hour;

    //RTC_Init(RTC_LOSC,RTC_HOUR24);
    //RTC_Init(RTC_LRC,RTC_HOUR12);
    RTC_Init(RTC_LRC, RTC_HOUR24);

    /* ��ȡ�ϵ�Ĭ��ֵ */
    mode = RTC_ReadHourmode();
    RTC_ReadSecond();
    RTC_ReadMinute();
    RTC_ReadHour(&meridiem);
    RTC_ReadDay();
    RTC_ReadMonth();
    RTC_ReadYear();
    RTC_ReadWeek();
    RTC_ReadWeekAlarmMinute();
    RTC_ReadWeekAlarmHour(&meridiem);
    RTC_ReadWeekAlarmWeek();
    RTC_ReadDayAlarmMinute();
    RTC_ReadDayAlarmHour(&meridiem);

    /* д���µ�ֵ */
    RTC_WriteWeekAlarmMinute(25);
    wa_min = RTC_ReadWeekAlarmMinute();

    RTC_WriteWeekAlarmHour(21, 0);
    wa_hour = RTC_ReadWeekAlarmHour(&meridiem);

    RTC_WriteWeekAlarmWeek(6);
    wa_week = RTC_ReadWeekAlarmWeek();

    RTC_WriteDayAlarmMinute(30);
    da_min = RTC_ReadDayAlarmMinute();

    RTC_WriteDayAlarmHour(7, 1);
    da_hour = RTC_ReadDayAlarmHour(&meridiem);

    RTC_WriteWeek(3);
    week = RTC_ReadWeek();

    RTC_WriteYear(2017);
    year = RTC_ReadYear();

    RTC_WriteMonth(6);
    month = RTC_ReadMonth();

    RTC_WriteDay(29);
    day = RTC_ReadDay();

    RTC_WriteHour(14, 1);
    hour = RTC_ReadHour(&meridiem);

    RTC_WriteMinute(58);
    min = RTC_ReadMinute();

    RTC_WriteSecond(30);
    sec = RTC_ReadSecond();

    /* ��ȡ��ֵ */
    if ((mode != RTC_HOUR24)
            || (sec != 30) || (min != 58) || (hour != 14) || (day != 29) || (month != 6) || (year != 2017) || (week != 3)
            || (wa_min != 25) || (wa_hour != 21) || (wa_week != 6)
            || (da_min != 30) || (da_hour != 7))
        return ERROR;

    return SUCCESS;
}

/*********************************************************
������: int main(void)
��  ��: ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
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

    while (1)
    {
        if (ERROR == RTC_Test())                                  //RTC��дʱ��
        {
            GPIO_WriteBit(GPIO_Pin_A6, 0);
            GPIO_WriteBit(GPIO_Pin_A7, 0);
            GPIO_WriteBit(GPIO_Pin_A8, 0);
            GPIO_WriteBit(GPIO_Pin_A9, 0);
            Delay_100us(500);
            GPIO_WriteBit(GPIO_Pin_A6, 1);
            GPIO_WriteBit(GPIO_Pin_A7, 1);
            GPIO_WriteBit(GPIO_Pin_A8, 1);
            GPIO_WriteBit(GPIO_Pin_A9, 1);
            Delay_100us(500);
        }
        else
        {
            GPIO_WriteBit(GPIO_Pin_A6, 0);
            GPIO_WriteBit(GPIO_Pin_A7, 0);
            GPIO_WriteBit(GPIO_Pin_A8, 0);
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        }
    }
}
