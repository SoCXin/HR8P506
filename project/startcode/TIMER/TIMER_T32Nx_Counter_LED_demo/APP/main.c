/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  32λ������ʾ������
            PB0���������½��ط����źţ�LED��ʾ���뷽����Ƶ�ʣ������ʾ֧��9999Hz
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main(void)
{
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    LEDInit();
    T32N0CNT_Init();
    T16N2Init();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {
        if (g_1s_flag == 1)
        {
            g_1s_flag = 0;
            DispHextoBcd(count, g_led_buf);
            count = 0;
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

