/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LED演示主程序
          循环计数0000-9999，每隔1s计数一次，按键K5（PB9）按下清零(按键使用中断模式输入)，核心板ZERO需要短接
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint32_t cnt;
    uint8_t com;
    uint8_t g_led_buf[4];
    KINT_InitSettingType y;

    cnt = 0;
    com = 0;

    SystemInit();
    GPIOInit();
    T16N3Init();

    y.IE_Set = KINT_IE_Set_Enable;
    y.Trigger_Style = KINT_Trigger_Trailing_Edge;
    KINT_Init(GPIO_Pin_B9, &y);                     //初始化按键中断PB9

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

        if (1 == g_key_flag)
        {
            g_key_flag = 0;
            cnt = 0;
        }
    }
}
