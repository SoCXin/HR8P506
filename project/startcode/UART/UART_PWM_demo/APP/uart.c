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
������: void UARTInit(void)
��  ��: UART��ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void UARTInit(void)
{
    GPIO_InitSettingType x;
    UART_InitStruType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A23, &x);        //TXD - PA23

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Input;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &x);        //RXD - PA22

    y.UART_StopBits = UART_StopBits_1;     //ֹͣλ��1
    y.UART_TxMode = UART_DataMode_8Odd;    //�������ݸ�ʽ��8λ����+��У��
    y.UART_TxPolar = UART_Polar_Normal;    //���Ͷ˿ڼ��ԣ�����
    y.UART_RxMode = UART_DataMode_8;       //�������ݸ�ʽ��8λ����
    y.UART_RxPolar = UART_Polar_Normal; //���ն˿ڼ��ԣ�����
    y.UART_BaudRate = 1200;             //������
    y.UART_ClockSet = UART_Clock_1;     //ʱ��ѡ��Pclk
    UART_Init(UART0, &y);

    GPIO_TX0Config(UART_TXPLV_Low, UART_TX0PS_BUZ, UART_TYPE_TXD0, Enable);
    BUZC_Frequence(38000, Enable); //BUZ���38k


    UART_TBIMConfig(UART0, UART_TBIM_Byte);
    UART_RBIMConfig(UART0, UART_TBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, Enable);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, Enable);

    UART0_TxEnable();
    UART0_RxEnable();
}
