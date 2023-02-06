/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  timer.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/28
*��  ��:  Timerģ�����ͷ�ļ�
*��  ע:  
          ����������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "timer.h"

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
    T16Nx_PWMInitStruType z;	
    GPIO_InitSettingType y;

    /* ��ʼ��T16Nx��ʱ��*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //�ⲿʱ��PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWMģʽ
    x.T16Nx_PREMAT = 80;                        //Ԥ��Ƶ��Ϊ1:80
    T16Nx_BaseInit(T16N0, &x);                  //��ʼ����ʱ��T16N0

    /*����T16N0ͨ��0���*/
    z.T16Nx_MOE0 = Enable;                      //ͨ��0�������
    z.T16Nx_MOE1 = Enable;                      //ͨ��1�������
    z.T16Nx_POL0 = POSITIVE;                    //���������
    z.T16Nx_POL1 = POSITIVE;                    //���������
    z.T16Nx_PWMMODE = T16Nx_PWMMode_INDEP;      //����ģʽ���
    z.PWMDZE = Disable;                         //�رջ���ģʽ��������
    T16Nx_PMWOutInit(T16N0, &z);

    T16Nx_MAT0ITConfig(T16N0, T16Nx_Clr_Int);   //CNT0ƥ�䵽MAT0�������¼���
    T16Nx_MAT1ITConfig(T16N0, T16Nx_Go_No);     //CNT0ƥ�䵽MAT1��������
    T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_High); //CNT0ƥ�䵽MAT0�˿������
    T16Nx_MAT1Out0Config(T16N0, T16Nx_Out_Low); //CNT0ƥ�䵽MAT1�˿������
    T16Nx_SetCNT0(T16N0, 0);                    //����T16N0��ʼֵΪ0
    T16Nx_SetMAT0(T16N0, 1000);                 //����T16N0MAT0ֵΪ����
    T16Nx_SetMAT1(T16N0, 500);                  //����T16N0MAT1ֵΪռ�ձ�

    /*����T16N0 ͨ��1���*/
    T16Nx_MAT2ITConfig(T16N0, T16Nx_Clr_Int);   //CNT1ƥ�䵽MAT2�������¼���
    T16Nx_MAT3ITConfig(T16N0, T16Nx_Go_No);     //CNT1ƥ�䵽MAT3��������
    T16Nx_MAT2Out1Config(T16N0, T16Nx_Out_High); //CNT10ƥ�䵽MAT0�˿������
    T16Nx_MAT3Out1Config(T16N0, T16Nx_Out_Low); //CNT1ƥ�䵽MAT1�˿������
    T16Nx_SetCNT1(T16N0, 0);                    //����T16N0��ʼֵΪ0
    T16Nx_SetMAT2(T16N0, 1000);                 //����T16N0MAT2ֵΪ����
    T16Nx_SetMAT3(T16N0, 200);                  //����T16N0MAT3ֵΪռ�ձ�

    T16Nx_SetTOP0(T16N0, 1000);                 //���ü�����ֵ�Ĵ���0
    T16Nx_SetTOP1(T16N0, 1000);                 //���ü�����ֵ�Ĵ���1
    T16Nx_PTR_Config(T16N0, T16Nx_P0MAT0, Enable); //����PWM����ģʽADC����ʹ��

    T16Nx_ITConfig(T16N0, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N0_IRQn, NVIC_Priority_1, Enable);
		
    /* ��ʼ��PWM�����*/
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func2;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A6, &y);                 //����PA6ΪT16N0 ���ͨ��0
    GPIO_Init(GPIO_Pin_A7, &y);                 //����PA7ΪT16N0 ���ͨ��1

    T16Nx_Enable(T16N0);                        //ʹ��T16N0

    return;
}
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
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //��ʱ��������ģʽ
    x.T16Nx_PREMAT = 2;
    T16Nx_BaseInit(T16N3, &x);                          //��ʼ����ʱ��T16N3

    T16Nx_MAT0ITConfig(T16N3, T16Nx_Clr_Int);           //MAT0ƥ������
    T16Nx_SetCNT0(T16N3, 0);                            //����T16N3��ʼֵΪ0
    T16Nx_SetMAT0(T16N3, SystemCoreClock / 1000);       //����T16N3MAT0ֵ
    T16Nx_ITConfig(T16N3, T16Nx_IT_MAT0, Enable);       //ʹ��T16N3ƥ��0�ж�
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, Enable); //�ж�����
    T16Nx_Enable(T16N3);

    return;
}
