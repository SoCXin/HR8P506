/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������ж��շ���
*��  ע:  
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
    GPIO_Init(GPIO_Pin_A23, &x);            //TXD - PA23

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir  = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &x);            //RXD - PA22

    y.UART_StopBits = UART_StopBits_1;      //ֹͣλ��1
    y.UART_TxMode   = UART_DataMode_8;      //�������ݸ�ʽ��8λ����
    y.UART_TxPolar  = UART_Polar_Normal;    //���Ͷ˿ڼ��ԣ�����
    y.UART_RxMode   = UART_DataMode_8;      //�������ݸ�ʽ��8λ����
    y.UART_RxPolar  = UART_Polar_Normal;    //���ն˿ڼ��ԣ�����
    y.UART_BaudRate = 9600;                 //������
    y.UART_ClockSet = UART_Clock_1;         //ʱ��ѡ��Pclk
    UART_Init(UART0, &y);

    UART_TBIMConfig(UART0, UART_TBIM_Byte);
    UART_RBIMConfig(UART0, UART_TBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, Enable);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, Enable);

    UART0_TxEnable();
    UART0_RxEnable();
}

/*********************************************************
������: void UARTTxData(uint8_t *buf, uint8_t n)
��  ��: UART����������֡���
����ֵ: buf���������ݻ���
        n���������ݸ���
���ֵ: ��
����ֵ: ��
**********************************************************/
void UARTTxData(uint8_t *buf, uint8_t n)
{
    uint8_t i, check_sum;

    buf[0] = HEAD1;             //֡ͷ0x55
    buf[1] = HEAD2;             //֡ͷ0xAA
    buf[2] = SLAVE_ADDR;        //�豸��ַ

    check_sum = 0;

    for (i = 0; i < n - 3; i++)
        check_sum ^= buf[i];    //���������ֽڣ�����֡ͷ��������

    buf[n - 3] = check_sum;     //��ֵУ���
    buf[n - 2] = TAIL1;         //֡β0x5A
    buf[n - 1] = TAIL2;         //֡β0xA5
    UART_ITConfig(UART0, UART_IT_TB, Enable);    //ʹ�ܷ����жϣ����ж��жϲ�������������֡
}

/*********************************************************
������: uint8_t UARTRxData(uint8_t *buf, uint8_t n)
��  ��: UART����������֡���
����ֵ: ��
���ֵ: buf���������ݻ���
        n���������ݸ���
����ֵ: ��
**********************************************************/
uint8_t UARTRxData(uint8_t *buf, uint8_t n)
{
    uint8_t i, check_sum;

    if ((buf[0] != HEAD1)
            || (buf[1] != HEAD2)
            || (buf[n - 2] != TAIL1)
            || (buf[n - 1] != TAIL2))  //�ж�֡ͷ��֡β����
        return 1;

    if (buf[2] != SLAVE_ADDR)       //�жϴӻ���ַ��ƥ��
        return 1;

    check_sum = 0;

    for (i = 0; i < n - 3; i++)
        check_sum ^= buf[i];        //���������ֽڣ�����֡ͷ��������

    if (buf[n - 3] != check_sum)    //�ж�У��ʹ���
        return 1;

    return 0;                       //��ȷ�����֡����
}

