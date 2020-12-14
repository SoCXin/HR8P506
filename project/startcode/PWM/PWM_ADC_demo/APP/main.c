/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.02
*��  ��:  2017/06/29
*��  ��:  PWM����ADCʾ������
            ��PA6��PA7�������PWM���Σ�ʹ��PWM����ģʽ����ADC������10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint16_t ad_temp;

int main(void)
{
    uint16_t sum;
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemInit();
    DeviceClockAllEnable();

    LEDInit();
    ADCInit();
    T16N3Init();
    T16NxInit();

    while (1)
    {
        if (g_500ms_flag == 1)
        {
            g_500ms_flag = 0;
            sum = ad_temp;
            DispHextoBcd(sum, g_led_buf);
            ad_temp = 0;

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

