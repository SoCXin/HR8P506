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
������: void T32N0CNT_Init(void)
��  ��: T32N0������ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T32N0CNT_Init(void)
{
    T32Nx_BaseInitStruType x;
    GPIO_InitSettingType y;

    /* ��ʼ��T32N0��ʱ��*/
    x.T32Nx_ClkS = T32Nx_ClkS_CK0;   //�ⲿʱ��CK0
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Fall;
    x.T32Nx_Mode = T32Nx_Mode_TC0;  //��ʱ��������ģʽ
    x.T32Nx_PREMAT = 1;
    T32Nx_BaseInit(T32N0, &x); //��ʼ����ʱ��T32N0

    /*�ⲿʱ��PB0��ʼ��*/
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Input;
    y.Func = GPIO_Reuse_Func1;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &y);

    /* ���ü����������水��K4��K3���ͻ���PB0���Ų����½��� */
    T32Nx_MAT0ITConfig(T32N0, T32Nx_Clr_Int);           //MAT0ƥ������
    T32Nx_SetCNT(T32N0, 0);                             //����T32N0��ʼֵΪ0
    T32Nx_SetMAT0(T32N0, 1);                            //����T32N0MAT0ֵΪ1
    T32Nx_ITConfig(T32N0, T32Nx_IT_MAT0, Enable);       //ʹ��T32N0ƥ��0�ж�
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T32Nx_Enable(T32N0);

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
    T16Nx_BaseInit(T16N2, &x);                          //��ʼ����ʱ��T16N3

    T16Nx_MAT0ITConfig(T16N2, T16Nx_Clr_Int);           //MAT0ƥ������
    T16Nx_SetCNT0(T16N2, 0);                            //����T16N2��ʼֵΪ0
    T16Nx_SetMAT0(T16N2, SystemCoreClock / 1000);       //����T16N2MAT0ֵ
    T16Nx_ITConfig(T16N2, T16Nx_IT_MAT0, Enable);       //ʹ��T16N2ƥ��0�ж�
    NVIC_Init(NVIC_T16N2_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T16Nx_Enable(T16N2);

    return;
}

