/*********************************************************
*Copyright (C), 2019, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  timer.c
*��  ��:  AE Team
*��  ��:  V1.00
*��  ��:  2019/11/29
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
������: void T16NxInit(void)
��  ��: T16Nx��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16NxInit(void)
{
    T16Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T16Nx_PWMInitStruType z;

    SCU_TIMEREN_Typedef t16n0_t16n1_en;
    t16n0_t16n1_en.Word = 0;

    dutyindex = 0;
    dutyNext = 0;

    /* ��ʼ��T16Nx��ʱ��*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //�ⲿʱ��PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWMģʽ
    x.T16Nx_PREMAT = 1;                         //����Ƶ
    T16Nx_BaseInit(T16N0, &x);                  //��ʼ����ʱ��T16N0
    T16Nx_BaseInit(T16N1, &x);                  //��ʼ����ʱ��T16N1

    /*����T16Nxͨ�����*/
    z.T16Nx_MOE0 = Enable;                      //ͨ��0�������
    z.T16Nx_MOE1 = Enable;                      //ͨ��1�������
    z.T16Nx_POL0 = POSITIVE;                    //���������
    z.T16Nx_POL1 = POSITIVE;                    //���������
    z.T16Nx_PWMMODE = T16Nx_PWMMode_SYNC;       //ͬ��ģʽ���
    z.PWMDZE = Disable;                         //�رջ���ģʽ��������
    T16Nx_PMWOutInit(T16N0, &z);
    T16Nx_PMWOutInit(T16N1, &z);

    T16Nx_MAT0ITConfig(T16N0, T16Nx_Go_Int);     //CNT0ƥ�䵽MAT0��������
    T16Nx_MAT1ITConfig(T16N0, T16Nx_Go_Int);     //CNT0ƥ�䵽MAT1��������
    T16Nx_MAT2ITConfig(T16N0, T16Nx_Clr_Int);    //CNT0ƥ�䵽MAT2�������¼���
    T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_High); //CNT0ƥ�䵽MAT0�˿������
    T16Nx_MAT1Out0Config(T16N0, T16Nx_Out_Low);  //CNT0ƥ�䵽MAT1�˿������
    T16Nx_SetCNT0(T16N0, 0);                     //����T16N0��ʼֵ
    T16Nx_SetMAT0(T16N0, 800);                   //����T16N0 MAT0ֵ
    T16Nx_SetMAT1(T16N0, 1200);                  //����T16N0 MAT1ֵ
    T16Nx_SetMAT2(T16N0, 2000);                  //����T16N0 MAT2ֵ

    T16Nx_MAT0ITConfig(T16N1, T16Nx_Go_Int);     //CNT0ƥ�䵽MAT0��������
    T16Nx_MAT1ITConfig(T16N1, T16Nx_Go_Int);     //CNT0ƥ�䵽MAT1��������
    T16Nx_MAT2ITConfig(T16N1, T16Nx_Clr_Int);    //CNT0ƥ�䵽MAT2�������¼���
    T16Nx_MAT0Out0Config(T16N1, T16Nx_Out_High); //CNT0ƥ�䵽MAT0�˿������
    T16Nx_MAT1Out0Config(T16N1, T16Nx_Out_Low);  //CNT0ƥ�䵽MAT1�˿������
    T16Nx_SetCNT0(T16N1, 0);                     //����T16N1��ʼֵ
    T16Nx_SetMAT0(T16N1, 600);                   //����T16N1 MAT0ֵ
    T16Nx_SetMAT1(T16N1, 1400);                  //����T16N1 MAT1ֵ
    T16Nx_SetMAT2(T16N1, 2000);                  //����T16N1 MAT2ֵ

    T16Nx_ITConfig(T16N0, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N0_IRQn, NVIC_Priority_1, Enable);
    T16Nx_ITConfig(T16N1, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N1_IRQn, NVIC_Priority_1, Enable);
		
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func2;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A6, &y);                 //����PA6ΪT16N0 ���ͨ��0
    GPIO_Init(GPIO_Pin_A7, &y);                 //����PA7ΪT16N0 ���ͨ��1
    GPIO_Init(GPIO_Pin_A8, &y);                 //����PA8ΪT16N1 ���ͨ��0
    GPIO_Init(GPIO_Pin_A9, &y);                 //����PA9ΪT16N1 ���ͨ��1
		
    t16n0_t16n1_en.T16N0EN = Enable;
    t16n0_t16n1_en.T16N1EN = Enable;
    SCU_MultTimerEnable(t16n0_t16n1_en);         //SCUͬ������T16N0/T16N1

    return;
}

