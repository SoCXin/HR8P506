/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  uart.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  UART模块程序（中断收发）
*备  注:
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "uart.h"

uint8_t g_rxbuf[255];           /* 接收数据缓存 */
uint8_t g_rx_length;            /* 接收数据长度 */
uint8_t g_txbuf[255];           /* 发送数据缓存 */
uint8_t g_tx_length;            /* 发送数据长度 */
uint8_t g_rx_time;              /* 字节间隔 */
uint8_t g_tx_time;              /* 字节间隔 */
volatile uint8_t g_rx_count;            /* 接收字节计数 */
volatile uint8_t g_tx_count;            /* 发送字节计数 */
volatile uint8_t g_rx_start_flag;       /* 接收起始标志 */
volatile uint8_t g_tx_start_flag;       /* 发送起始标志 */
volatile uint8_t g_rx_finish_flag;      /* 接收完成标志 */
volatile uint8_t g_tx_finish_flag;      /* 发送完成标志 */

/*********************************************************
函数名: void UART_Pins_Init(void)
描  述: 初始化UART通讯IO
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void UART_Pins_Init(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A23, &x);        /* TXD - PA23 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Input;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &x);        /* RXD - PA22 */
}


/*********************************************************
函数名: void UARTInit(void)
描  述: UART初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void UARTInit(void)
{
    UART_InitStruType y;
    y.UART_ClockSet = UART_Clock_1;         /* 时钟选择：Pclk */
    y.UART_BaudRate = 115200;               /* 波特率:115200 */
    y.UART_StopBits = UART_StopBits_1;      /* 停止位：1 */
    y.UART_TxMode = UART_DataMode_8;        /* 发送数据格式：8位数据，无校验 */
    y.UART_TxPolar = UART_Polar_Normal;     /* 发送端口极性：正常 */
    y.UART_RxMode = UART_DataMode_8;        /* 接收数据格式：8位数据，无校验 */
    y.UART_RxPolar = UART_Polar_Normal;     /* 接收端口极性：正常 */
    UART_Init(UART0, &y);

    UART_Pins_Init();
    UART0_TxEnable();
}

