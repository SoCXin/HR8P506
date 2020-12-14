/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  PLL����
             PLL��Ƶ��48M�󣬶�ʱ��˸LD1ָʾ��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{

    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);    //PLLʹ�ܣ���Ƶ��48M���ɹرմ򿪷ֱ�۲�ָʾ����˸���� ,��PA6���θ�ֱ�ۣ�
    SCU->SCLKEN0.CLKFLT_BY = 0x55; //PLL��Ƶ��48Mʱ����Ҫ��·ʱ���˲���CLKFLT������ע�ʹ���
    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    T16N3Init();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {

        GPIO->PADATABCR.Word = 0x00000040; //PA6��0
        GPIO->PADATABSR.Word = 0x00000040; //PA6��1
//        GPIO->PADATABRR.Word = 0x00000040; //PA6ȡ��

    }
}

