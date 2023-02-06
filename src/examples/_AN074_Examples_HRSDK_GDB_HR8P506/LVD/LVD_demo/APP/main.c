/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LVDʾ�����򣺲��뿪����5V�л���3.3Vʱ��LVD������4V��ѹ�����л���5V�������LED1-LED4
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

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    SCU_RegUnLock();
    SCU_LVDVS_4V();
    SCU_LVDIFS_Fall();
    SCU_LVDFLT_Enable();
    NVIC_Init(NVIC_LVD_IRQn, NVIC_Priority_0, Enable); //�ж�����
    SCU_LVD_Enable();
    SCU_LVDIT_Enable();
    SCU_RegLock();

    while (1);
}
