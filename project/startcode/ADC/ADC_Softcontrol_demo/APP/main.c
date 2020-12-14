/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ADC��ʾ������
          ����10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��--������Ʋ�����ͣ
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{
    uint16_t sum;
    uint8_t g_led_buf[4];
    uint8_t com;

    com = 0;
    sum = 0;

    SystemInit();
    T16N3Init();
    LEDInit();
    ADCInit();

    while (1)
    {
        if (g_500ms_flag == 1)
        {
            g_500ms_flag = 0;
            sum = ADCRead();
            DispHextoBcd(sum, g_led_buf);
        }

        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);
            com++;

            if (com > 3)
                com = 0;
        }
    }
}
