/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  light.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/25
*��  ��:  LIGHTָʾ��ģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "light.h"

/***************************************************************
 ��������void LightInit(void)
 ��  ����LIGHTָʾ����˸��ʼ��
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void LightInit(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A6, &x);
    GPIO_Init(GPIO_Pin_A7, &x);
    GPIO_Init(GPIO_Pin_A8, &x);
    GPIO_Init(GPIO_Pin_A9, &x);

    return;
}
