/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  uart.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:
*备  注:   V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "uart.h"

/*********************************************************
函数名: void UARTInit(void)
描  述: UART初始化子程序
输入值: 无
输出值: 无
返回值: 无
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

    y.UART_StopBits = UART_StopBits_1;     //停止位：1
    y.UART_TxMode = UART_DataMode_8Odd;    //发送数据格式：8位数据+奇校验
    y.UART_TxPolar = UART_Polar_Normal;    //发送端口极性：正常
    y.UART_RxMode = UART_DataMode_8;       //接收数据格式：8位数据
    y.UART_RxPolar = UART_Polar_Normal; //接收端口极性：正常
    y.UART_BaudRate = 1200;             //波特率
    y.UART_ClockSet = UART_Clock_1;     //时钟选择：Pclk
    UART_Init(UART0, &y);

    GPIO_TX0Config(UART_TXPLV_Low, UART_TX0PS_BUZ, UART_TYPE_TXD0, Enable);
    BUZC_Frequence(38000, Enable); //BUZ输出38k


    UART_TBIMConfig(UART0, UART_TBIM_Byte);
    UART_RBIMConfig(UART0, UART_TBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, Enable);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, Enable);

    UART0_TxEnable();
    UART0_RxEnable();
}
