/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  RTC模块例程 (配置字CFG_OSCMD一定选择LP模式！！！！)
            RTC写一个固定时间，读出时间是否与写入时间一致，不一致则LD1-LD4灯间隔闪烁，一致则LD1-LD4常亮；
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

/*********************************************************
函数名: uint32_t RTC_Test(void)
描  述: 实时时钟API测试
输入值: 无
输出值: 无
返回值: SUCCESS: 测试成功
        ERROR: 测试失败
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

    /* 读取上电默认值 */
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

    /* 写入新的值 */
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

    /* 读取新值 */
    if ((mode != RTC_HOUR24)
            || (sec != 30) || (min != 58) || (hour != 14) || (day != 29) || (month != 6) || (year != 2017) || (week != 3)
            || (wa_min != 25) || (wa_hour != 21) || (wa_week != 6)
            || (da_min != 30) || (da_hour != 7))
        return ERROR;

    return SUCCESS;
}

/*********************************************************
函数名: int main(void)
描  述: 主函数
输入值: 无
输出值: 无
返回值: 无
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
        if (ERROR == RTC_Test())                                  //RTC读写时间
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
