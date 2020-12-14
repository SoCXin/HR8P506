/*********************************************************
*Copyright (C), 2019, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  AE Team
*��  ��:  V1.00
*��  ��:  2019/11/29
*��  ��:  PWMʾ������
                          SCUͬ��������T16N��PA6��PA7��PA8��PA9�����·ͬ�����Ķ���PWM��
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

    while (1);
}
