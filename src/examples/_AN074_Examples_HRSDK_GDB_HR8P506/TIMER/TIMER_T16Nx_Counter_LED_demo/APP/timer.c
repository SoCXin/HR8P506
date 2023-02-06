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

/*********************************************************
������: void T16N3CNT_Init(void)
��  ��: T16N3������ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N3CNT_Init(void)
{
    T16Nx_BaseInitStruType x;
    GPIO_InitSettingType y;

    /* ��ʼ��T16N3��ʱ��*/
    x.T16Nx_ClkS = T16Nx_ClkS_CK0;      //�ⲿʱ��CK0
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Fall;
    x.T16Nx_Mode = T16Nx_Mode_TC0;      //��ʱ��������ģʽ
    x.T16Nx_PREMAT = 1;
    T16Nx_BaseInit(T16N3, &x);          //��ʼ����ʱ��T16N3

    /*�ⲿʱ��PB0��ʼ��*/
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Input;
    y.Func = GPIO_Reuse_Func3;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &y);

    /* ���ü������½��� */
    T16Nx_MAT0ITConfig(T16N3, T16Nx_Clr_Int);           //MAT0ƥ������
    T16Nx_SetCNT0(T16N3, 0);                            //����T16N3��ʼֵΪ0
    T16Nx_SetMAT0(T16N3, 1);                            //����T16N3MAT0ֵΪ1
    T16Nx_ITConfig(T16N3, T16Nx_IT_MAT0, Enable);       //ʹ��T16N3ƥ��0�ж�
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T16Nx_Enable(T16N3);

    return;
}

/*********************************************************
������: void T16N3Init(void)
��  ��: T16N3��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N2Init(void)
{
    T16Nx_BaseInitStruType x;

    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;                     //�ڲ�ʱ��PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //��ʱ��������ģʽ
    x.T16Nx_PREMAT = 4;
    T16Nx_BaseInit(T16N2, &x);                          //��ʼ����ʱ��T16N2

    T16Nx_MAT0ITConfig(T16N2, T16Nx_Clr_Int);           //MAT0ƥ������
    T16Nx_SetCNT0(T16N2, 0);                            //����T16N2��ʼֵΪ0
    T16Nx_SetMAT0(T16N2, SystemCoreClock / 1000);       //����T16N2MAT0ֵ
    T16Nx_ITConfig(T16N2, T16Nx_IT_MAT0, Enable);       //ʹ��T16N2ƥ��0�ж�
    NVIC_Init(NVIC_T16N2_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T16Nx_Enable(T16N2);

    return;
}

