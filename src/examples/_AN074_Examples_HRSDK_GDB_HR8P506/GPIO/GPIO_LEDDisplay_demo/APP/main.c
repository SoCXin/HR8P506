/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LED演示主程序
          循环计数0000-9999，每隔1s计数一次
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint32_t cnt;
    uint8_t com;
    uint8_t g_led_buf[4];

    cnt = 0;
    com = 0;

    SystemInit();
    LEDInit();
    T16N3Init();

    DispHextoBcd(cnt, g_led_buf);

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;

            if (com >= COMMAX)
                com = 0;

            LEDDisplayData(com, g_led_buf[com]);
            com++;
        }

        if (g_1s_flag == 1)
        {
            g_1s_flag = 0;
            DispHextoBcd(cnt, g_led_buf);
            cnt++;

            if (cnt > 9999)
                cnt = 0;
        }
    }
}
