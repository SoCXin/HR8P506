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
函数名: void EUARTInit(void)
描  述: EUART初始化子程序
输入值: 无
输出值: 无
返回值: 无
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

    y.EUART_StopBits = EUART_StopBits_1;  //停止位：1
    y.EUART_TxMode = EUART_DataMode_8;    //发送数据格式：8位数据
    y.EUART_TxPolar = EUART_Polar_Normal; //发送端口极性：正常
    y.EUART_RxMode = EUART_DataMode_8;    //接收数据格式：8位数据
    y.EUART_RxPolar = EUART_Polar_Normal; //接收端口极性：正常
    y.EUART_BaudRate = 9600;             //波特率
    y.EUART_ClockSet = EUART_Clock_1;     //时钟选择：Pclk
    EUART_Init(&y);

    EUART_ModeConfig(EUART_Mode_Uart);
    EUART_TBIMConfig(EUART_TRBIM_Byte);
    EUART_RBIMConfig(EUART_TRBIM_Byte);
    EUART_ITConfig(EUART_IT_RB, Enable);
    NVIC_Init(NVIC_EUART0_IRQn, NVIC_Priority_1, Enable);

    EUART_TxEnable();
    EUART_RxEnable();
}
