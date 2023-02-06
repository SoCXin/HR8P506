/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LCD演示主程序
          上电显示“12:00”，然后显示实时时钟
         （1）单击K4：调节分钟值
         （2）单击K3：调节小时值
         （3）单击K2：切换显示模式，“小时:分钟”/“分钟:秒”
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

/*********************************************************
函数名: void RealTime(void)
描  述: 每秒调用一次更新时间
输入值: 无
输出值: 无
返回值: 无
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
函数名: int main(void)
描  述: 主函数
输入值: 无
输出值: 无
返回值: 无
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
                case 4:                                 /* 调整分钟*/
                    if (display_flag == 0)
                    {
                        clock_minute++;

                        if (clock_minute >= 60)
                            clock_minute = 0;
                    }

                    break;

                case 3:                                 /* 调整小时*/
                    if (display_flag == 0)
                    {
                        clock_hour++;

                        if (clock_hour >= 24)
                            clock_hour = 0;
                    }

                    break;

                case 2:                                 /* 小时分钟/分钟秒切换*/
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


