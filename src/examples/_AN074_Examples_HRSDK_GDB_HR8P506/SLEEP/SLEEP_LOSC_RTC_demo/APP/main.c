/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:
*��  ��:  V1.01
*��  ��:  2018/03/26
*��  ��:  sleepʾ�����򣬵���ʹ���Ӱ��������(��Ҫ�Ͽ��Ӱ��ϵ�Դָʾ�Ƶ���������)��
          �������ѹ����3.6V�������߳���RTC�뻽�Ѳ���תPA23
          �������ѹ����4v�˳����߳���PA23������ת
          ���߳�����Դ���£�
          1.WDT���Ѻ��幷��PA23��ת1��
          2.��������(PA22��0)��PA23������ת7��
          3.RTC�뻽��PA23��תһ��
          4.LVD����ϵͳ��λ�˳����ߺ���
          ע�⣺������LVD�������鲢ʹ�õ������������ʱ���������������ں�����(΢�����������Ӱ�칩���ѹ)
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t g_sleep_flag = 0;
int main(void)
{
    uint32_t i;
    GPIO_InitSettingType x;
    SystemInit();
    DeviceClockAllEnable();
    //for(i=0; i<1055350; i++);
    //���¿�ʼ���LVD��ѹ�Ƿ��������͹���״̬
    SCU_RegUnLock();
    SCU_LVDIFS_High(); //LVD�͵�ѹ���
    SCU_LVDVS_3V6();   //LVD���ߵ�ѹ3.6V
    SCU_LVDFLT_Enable();
    SCU_LVDIT_Enable();
    SCU_LVD_Enable();
    SCU->PWRC.PORRSTF = 0;   //��Ҫ���SOFT_RSTF��ʶ���Ƚ�PORRSTF����
    SCU_RegLock();

    if (SCU_GetLVDFlagStatus(SCU_LVDFlag_Out) == SET) //LVD��⵽��ѹ����4V
    {
        sleep(); //�������ߺ���
    }

    //���¿�ʼ������ѭ����ʼ��
    SCU_RegUnLock();
    SCU_LVDIFS_Rise(); //LVD��ѹ���ͼ��
    NVIC_Init(NVIC_LVD_IRQn, NVIC_Priority_0, Enable); //LVD�ж�����
    SCU_OpenXTAL();  //ʹ���ⲿ����
    SCU_RegLock();



    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func0;
    x.Dir = GPIO_Direction_Output;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PDE = GPIO_PDE_Input_Disable;
    x.PUE = GPIO_PUE_Input_Disable;
    GPIO_Init(GPIO_Pin_A23, &x); //PA23����Ϊ���
    GPIO_SetBit(GPIO_Pin_A6);
    GPIO_Init(GPIO_Pin_A6, &x); //PA23����Ϊ���

    if (SCU->PWRC.SOFT_RSTF == 0) //����û�о�������λ
    {
        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6��ת
    }

    //for(i=0; i<655350; i++);

    while (1)
    {
        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
        WDT_Clear();  //�幷

        if (g_sleep_flag == 1)  //LVD�жϼ�⵽VDD��ѹ����3.6V����λ�������ߺ���
        {
            NVIC_SystemReset();
        }
    }
}
