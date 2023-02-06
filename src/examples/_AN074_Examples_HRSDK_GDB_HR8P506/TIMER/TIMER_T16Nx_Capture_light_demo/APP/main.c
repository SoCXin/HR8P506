/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:   Liut
*��  ��:  V1.01
*��  ��:  2017/06/30
*��  ��:  16λ���Ų�׽��ʾ������
          PB0�������������ط����źţ�T16N3ÿ����2�η����ж�һ�Σ���׽ֵ����buffer
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint32_t count00 = 0;
uint32_t buf00[50];

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    T16N3CAP_Init();                //PB0����

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1);
}

