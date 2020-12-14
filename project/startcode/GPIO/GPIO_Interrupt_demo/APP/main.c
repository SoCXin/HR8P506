/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LED��ʾ������
          ѭ������0000-9999��ÿ��1s����һ�Σ�����K5��PB9����������(����ʹ���ж�ģʽ����)�����İ�ZERO��Ҫ�̽�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
    KINT_Init(GPIO_Pin_B9, &y);                     //��ʼ�������ж�PB9

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
