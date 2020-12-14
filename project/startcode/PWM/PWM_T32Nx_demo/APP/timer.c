/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  timer.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/28
*��  ��:  Timerģ�����ͷ�ļ�
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "timer.h"

unsigned int Period = 1000;
unsigned int dutytab[6] = {0, 200, 400, 600, 800, 1000};
unsigned int dutyindex;
unsigned int dutyNext;

/*********************************************************
������: void T32NxInit(void)
��  ��: T32Nx��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T32NxInit(void)
{
    T32Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T32Nx_PWMInitStruType z;

    dutyindex = 0;
    dutyNext = 0;

    /* ��ʼ��PWM�����  */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func1;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B1, &y);                     //����PB1ΪT32N0 ���ͨ��1

    /* ��ʼ��T32Nx��ʱ��*/
    x.T32Nx_ClkS = T32Nx_ClkS_PCLK;                 //�ڲ�PCLK
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Rise;
    x.T32Nx_Mode = T32Nx_Mode_PWM;                  //��ʱ��������ģʽ
    x.T32Nx_PREMAT = 20;                            //Ԥ��Ƶ��Ϊ1:20
    T32Nx_BaseInit(T32N0, &x);                      //��ʼ����ʱ��T32N0

    /*��ʼ��T32N0PWM���*/
    z.T32Nx_MOE0 = Disable;
    z.T32Nx_MOE1 = Enable;                          //ʹ��ͨ��1���
    T32Nx_PMWOutInit(T32N0, &z);                    //��ʼ��T32N0ΪPWMģʽ

    T32Nx_MAT2ITConfig(T32N0, T32Nx_Clr_Int);       //CNT0ƥ�䵽MAT2�������¼���
    T32Nx_MAT3ITConfig(T32N0, T32Nx_Go_Int);        //CNT0ƥ�䵽MAT3��������
    T32Nx_MAT2Out1Config(T32N0, T32Nx_Out_High);    //CNT0ƥ�䵽MAT3�˿������
    T32Nx_MAT3Out1Config(T32N0, T32Nx_Out_Low);     //CNT0ƥ�䵽MAT3�˿������
    T32Nx_SetCNT(T32N0, 0);                         //����T32N0��ʼֵΪ0
    T32Nx_SetMAT2(T32N0, Period);                   //����T32N0MAT2ֵΪ����
    T32Nx_SetMAT3(T32N0, dutytab[1]);               //����T32N0MAT3ֵΪռ�ձ�

    T32Nx_ITConfig(T32N0, T32Nx_IT_MAT2, Enable);
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable);
    T32Nx_Enable(T32N0);                            //ʹ��T32N0��ʱ��

    return;
}

