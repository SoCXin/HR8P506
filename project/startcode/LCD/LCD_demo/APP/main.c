/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LCD��ʾ������
          �ϵ���ʾ��12:00����Ȼ����ʾʵʱʱ��
         ��1������K4�����ڷ���ֵ
         ��2������K3������Сʱֵ
         ��3������K2���л���ʾģʽ����Сʱ:���ӡ�/������:�롱
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

/*********************************************************
������: void RealTime(void)
��  ��: ÿ�����һ�θ���ʱ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void RealTime(void)
{
    clock_second++;

    if (clock_second >= 60)
    {
        clock_second = 0;
        clock_minute ++;
    }

    if (clock_minute >= 60)
    {
        clock_minute = 0;
        clock_hour ++;
    }

    if (clock_hour >= 24)
    {
        clock_hour = 0;
    }
}

/*********************************************************
������: int main(void)
��  ��: ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
int main()
{
    uint8_t display_flag = 0;
    uint8_t flick_flag = 0;
    uint8_t key = 0;

    SystemInit();
    DeviceClockAllEnable();

    KeyInit();
    LCDInit();
    T16N3Init();

    clock_hour = 12;
    clock_minute = 1;
    clock_second = 0;

    while (1)
    {
        if (1 == g_10ms_flag)
        {
            g_10ms_flag = 0;
            key = KeyGetValue();

            switch (key)
            {
                case 4:                                 /* ��������*/
                    if (display_flag == 0)
                    {
                        clock_minute++;

                        if (clock_minute >= 60)
                            clock_minute = 0;
                    }

                    break;

                case 3:                                 /* ����Сʱ*/
                    if (display_flag == 0)
                    {
                        clock_hour++;

                        if (clock_hour >= 24)
                            clock_hour = 0;
                    }

                    break;

                case 2:                                 /* Сʱ����/�������л�*/
                    display_flag = !display_flag;
                    break;

                default:
                    key = 0;
                    break;
            }
        }

        if (1 == g_500ms_flag)
        {
            g_500ms_flag = 0;
            flick_flag = !flick_flag;
        }

        if (1 == g_1s_flag)
        {
            g_1s_flag = 0;
            RealTime();
        }

        if (0 == display_flag)
            LCDDisplayData(clock_hour, clock_minute, flick_flag);
        else
            LCDDisplayData(clock_minute, clock_second, flick_flag);
    }

}


