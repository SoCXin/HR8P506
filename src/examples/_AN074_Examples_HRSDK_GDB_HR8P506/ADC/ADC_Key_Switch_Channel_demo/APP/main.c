/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ADC��ʾ������
          ����10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��������K1�л�ADCͨ�����ֱ����AIN1��AIN0--������Ʋ�����ͣ
*��  ע:
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t KeyGetValue(void);
void ADC_Set_CH(ADC_TYPE_CHS AdcCH);

int main()
{
    uint16_t sum;
    uint8_t g_led_buf[4];
    uint8_t com;
    uint8_t channel_flag = 0;

    com = 0;
    sum = 0;

    SystemInit();
    T16N3Init();
    LEDInit();
    ADCInit();

    while (1)
    {
        if (channel_flag == 0)                          //ѡ��ͨ��1
        {
            ADC_Set_CH(ADC_CHS_AIN1);
        }
        else                                            //ѡ��ͨ��0
        {
            ADC_Set_CH(ADC_CHS_AIN0);
        }

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

        if (1 == g_10ms_flag)                           //���10msɨ�谴��
        {
            g_10ms_flag = 0;

            if (1 == KeyGetValue())
            {
                channel_flag = ~channel_flag;       //�л�ADCģ��ͨ��
            }
        }
    }
}
