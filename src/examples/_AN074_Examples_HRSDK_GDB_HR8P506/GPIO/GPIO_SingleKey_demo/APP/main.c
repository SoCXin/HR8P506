/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LED��ʾ������
          �����ѭ������0000-9999��ÿ��1s����һ�Σ�����K5(PB9)�������㣨����ʹ��ɨ�跽ʽ���룩�����İ�ZERO��Ҫ�̽�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
    KeyInit();

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

        if (5 == KeyGetValue())
        {
            g_key_flag = 0;
            cnt = 0;
        }
    }
}
