/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/28
*��  ��:  ���������ʾ������
*��  ע:  
          ����K1��������Ч����LED1����
          ����K2���ͷ���Ч����LED2��ת
          ����K3��������Ч����LED1-LED4��ˮ����
          ����K4��������Ч����LED4-LED1��ˮ����
          ����K5��������Ч�����İ�ZERO��Ҫ�̽ӣ�������LEDȫ��Ϩ��
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{
    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    T16N3Init();
    LightInit();
    KeyInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    g_10ms_flag = 0;
    g_200ms_flag = 0;
    g_200ms_cnt = 0;
    g_key_cmd = 0;
    flag = 0;

    while (1)
    {
        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;
            g_key_cmd = KeyGetValue();

            switch (g_key_cmd)
            {
                case 1:
                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    break;

                case 2:
                    if (flag == 1)
                    {
                        flag = 0;
                        GPIO_WriteBit(GPIO_Pin_A7, 1);
                    }
                    else
                    {
                        flag = 1;
                        GPIO_WriteBit(GPIO_Pin_A7, 0);
                    }

                    break;

                case 3:
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);

                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A7, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A8, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A9, 0);
                    Delay1ms(500);

                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);
                    break;

                case 4:
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);

                    GPIO_WriteBit(GPIO_Pin_A9, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A8, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A7, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    Delay1ms(500);

                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);
                    break;

                case 5:
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);
                    break;

                default:
                    g_key_cmd = 0;
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    break;
            }
        }
    }
}
