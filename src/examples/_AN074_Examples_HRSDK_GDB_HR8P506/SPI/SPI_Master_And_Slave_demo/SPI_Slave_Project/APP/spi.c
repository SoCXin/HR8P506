/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/09
*描  述:  SPI从机模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"


/*********************************************************
函数名: void SPI1_Pins_Init(void)
描  述: SPI主机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1_Pins_Init(void)
{
    GPIO_InitSettingType x;

    /* PA 2 3 4 5 -FUNC3 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func3;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A2, &x);                /* NSS - PA2 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func3;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A5, &x);                /* MOSI - PA5 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func3;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A3, &x);                /* SCK - PA3 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func3;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A4, &x);                /* MISO - PA4 */
}

/*********************************************************
函数名: void SPIInit(void)
描  述: SPI主机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1Init(void)
{
    SPI_InitStruType y;
    y.SPI_Freq = SystemCoreClock;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Slave;
    y.SPI_DW = 7;                               /* 位宽:7+1位 */
    y.SPI_DelayRec = Disable;
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0x0;
    SPI_Init(SPI1, &y);

    SPI_RBIMConfig(SPI1, SPI_IType_BYTE);       /* RB0满产生中断 */
    SPI_TBIMConfig(SPI1, SPI_IType_BYTE);       /* TB0空产生中断 */
    SPI_ITConfig(SPI1, SPI_IT_TB, Enable);      /* 打开发送缓冲器空中断 */
    SPI_ITConfig(SPI1, SPI_IT_RB, Enable);      /* 打开接收缓冲器慢中断 */
    NVIC_Init(NVIC_SPI1_IRQn, NVIC_Priority_0, Enable);

    SPI1_Pins_Init();
    SPI1_RecEnable();                           /* 使能SPI接收 */
    SPI1_Enable();                              /* 使能SPI */
}

