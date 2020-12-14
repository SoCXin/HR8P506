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
void T16N3Init(void)
{
    T16Nx_BaseInitStruType x;

    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;                     //�ڲ�ʱ��PCLK
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //��ʱ��������ģʽ
    x.T16Nx_PREMAT = 2;
    x.T16Nx_SYNC = Disable;
    T16Nx_BaseInit(T16N3, &x);                          //��ʼ����ʱ��T16N3

    T16Nx_MAT0ITConfig(T16N3, T16Nx_Clr_Int);           //MAT0ƥ������
    T16Nx_SetCNT0(T16N3, 0);                            //����T16N3��ʼֵΪ0
    T16Nx_SetMAT0(T16N3, SystemCoreClock / 1000);       //����T16N3MAT0ֵ
    T16Nx_ITConfig(T16N3, T16Nx_IT_MAT0, Enable);       //ʹ��T16N3ƥ��0�ж�
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T16Nx_Enable(T16N3);

    return;
}

