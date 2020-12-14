/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  motor.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/07/13
*��  ��:  �����������
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "motor.h"

/*********************************************************
������: void MotorInit(void)
��  ��: ���������ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void MotorInit(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func0;
    x.Dir = GPIO_Direction_Output;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIO_Pin_A6, &x);
    GPIO_Init(GPIO_Pin_A7, &x);
    GPIO_Init(GPIO_Pin_A8, &x);
    GPIO_Init(GPIO_Pin_A9, &x);
}

/*********************************************************
������: void MotorWrite(uint8_t data)
��  ��: ���ò����������һ��ת������
����ֵ: data: �����������һ��ת������
���ֵ: ��
����ֵ: ��
**********************************************************/
void MotorWrite(uint8_t data)
{
    if (data & 0x01)
        GPIO_WriteBit(GPIO_Pin_A9, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A9, 0);

    if (data & 0x2)
        GPIO_WriteBit(GPIO_Pin_A8, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A8, 0);

    if (data & 0x4)
        GPIO_WriteBit(GPIO_Pin_A7, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A7, 0);

    if (data & 0x8)
        GPIO_WriteBit(GPIO_Pin_A6, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A6, 0);

    return;
}
