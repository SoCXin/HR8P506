/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:
*��  ע:   V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "uart.h"

/*********************************************************
������: void EUARTInit(void)
��  ��: EUART��ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void EUARTInit(void)
{
    GPIO_InitSettingType x;
    EUART_InitStruType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B5, &x);        //TXD - PB5

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Input;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B4, &x);        //RXD - PB4

    y.EUART_StopBits = EUART_StopBits_1;  //ֹͣλ��1
    y.EUART_TxMode = EUART_DataMode_8;    //�������ݸ�ʽ��8λ����
    y.EUART_TxPolar = EUART_Polar_Normal; //���Ͷ˿ڼ��ԣ�����
    y.EUART_RxMode = EUART_DataMode_8;    //�������ݸ�ʽ��8λ����
    y.EUART_RxPolar = EUART_Polar_Normal; //���ն˿ڼ��ԣ�����
    y.EUART_BaudRate = 9600;             //������
    y.EUART_ClockSet = EUART_Clock_1;     //ʱ��ѡ��Pclk
    EUART_Init(&y);

    EUART_ModeConfig(EUART_Mode_Uart);
    EUART_TBIMConfig(EUART_TRBIM_Byte);
    EUART_RBIMConfig(EUART_TRBIM_Byte);
    EUART_ITConfig(EUART_IT_RB, Enable);
    NVIC_Init(NVIC_EUART0_IRQn, NVIC_Priority_1, Enable);

    EUART_TxEnable();
    EUART_RxEnable();
}
