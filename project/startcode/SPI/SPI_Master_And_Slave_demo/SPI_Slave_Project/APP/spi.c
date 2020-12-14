/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  SPI从机模块程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"

/*********************************************************
函数名: void SPIInit(void)
描  述: SPI从机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1Init(void)
{
    GPIO_InitSettingType x;
    SPI_InitStruType y;

    /* PA 24 25 26 27 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;


    GPIO_Init(GPIO_Pin_A25, &x);                //DI  - PA25
    GPIO_Init(GPIO_Pin_A26, &x);                //CLK - PA26
    GPIO_Init(GPIO_Pin_A27, &x);                //CS  - PA27

    x.Dir = GPIO_Direction_Output;
    GPIO_Init(GPIO_Pin_A24, &x);                //DO  - PA24

    y.SPI_Freq = 10000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Slave;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                   //延时半周期
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         //按照结构体的参数配置SPI

    SPI_ITConfig(SPI1, SPI_IT_NSS, Enable);
    NVIC_Init(NVIC_SPI1_IRQn, NVIC_Priority_0, Enable);

    SPI1_RecEnable();
    SPI1_Enable();                              //使能SPI
}

