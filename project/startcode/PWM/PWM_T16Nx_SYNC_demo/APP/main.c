/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.02
*��  ��:  2017/06/29
*��  ��:  PWMʾ������
            ��PA6��PA7�������ͬ��PWM����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);
    SystemInit();
    DeviceClockAllEnable();

    T16NxInit();

    while (1)
    {
    }
}

