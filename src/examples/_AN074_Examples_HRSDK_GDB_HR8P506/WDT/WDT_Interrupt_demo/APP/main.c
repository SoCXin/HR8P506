/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ���Ź�ʾ������
            ���Ź���ʱ2s���ڿ��Ź��жϺ����У�ι���򲻸�λ��LD1-LD4��˸��������ι����λ��LD1-LD4��������˸
            ע���ж�һ���������������WDTINTENʹ�ܣ���������������
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

/*********************************************************
������: int main(void)
��  ��: ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
int main(void)
{

    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_32M, Enable);    //PLL??,???48M(????????????????
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
