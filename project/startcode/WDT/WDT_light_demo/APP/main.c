/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ���Ź�ʾ������
        LD1-LD4���200ms��˸�����Ź���ʱ2s��ι���򲻸�λ��LD1-LD4������˸����ι����λ��LD4���ֲ�������˸
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();
    WdtInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {
        WDT_Clear();                        //ι������λ����ι����λ

        GPIO_WriteBit(GPIO_Pin_A6, 1);
        GPIO_WriteBit(GPIO_Pin_A7, 1);
        GPIO_WriteBit(GPIO_Pin_A8, 1);
        GPIO_WriteBit(GPIO_Pin_A9, 1);
        Delay_100us(2000);

        GPIO_WriteBit(GPIO_Pin_A6, 0);
        GPIO_WriteBit(GPIO_Pin_A7, 0);
        GPIO_WriteBit(GPIO_Pin_A8, 0);
        GPIO_WriteBit(GPIO_Pin_A9, 0);
        Delay_100us(2000);
    }
}
