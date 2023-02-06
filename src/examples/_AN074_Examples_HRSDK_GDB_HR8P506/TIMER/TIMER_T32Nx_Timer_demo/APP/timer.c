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
������: void T16N3Init(void)
��  ��: T16N3��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T32NxInit(void)
{
    T32Nx_BaseInitStruType x;

    /* ��ʼ��T16Nx��ʱ��*/
    x.T32Nx_ClkS = T32Nx_ClkS_PCLK;             //�ⲿʱ��CK0
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Rise;
    x.T32Nx_Mode = T32Nx_Mode_TC0;              //��ʱ��������ģʽ
    x.T32Nx_PREMAT = 1;
    T32Nx_BaseInit(T32N0, &x);                  //��ʼ����ʱ��T32N0

    /* ���ö�ʱ�� */
    T32Nx_MAT0ITConfig(T32N0, T32Nx_Clr_Int);   //MAT0ƥ������
    T32Nx_SetCNT(T32N0, 0);                     //����T32N0��ʼֵΪ0
    T32Nx_SetMAT0(T32N0, 400000);               //����T32N0MAT0ֵΪ40000
    T32Nx_ITConfig(T32N0, T32Nx_IT_MAT0, Enable); //ʹ��T32N0ƥ��0�ж�
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T32Nx_Enable(T32N0);

    return;
}

