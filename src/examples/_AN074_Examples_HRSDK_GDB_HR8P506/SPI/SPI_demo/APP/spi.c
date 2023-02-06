/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/14
*描  述:  SPI主机模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"
#include "systick.h"

#define CS_EN()  GPIO_SetBit(SPI_NSS)
#define CS_DIS() GPIO_ResetBit(SPI_NSS)

uint8_t g_wbuf[260];
uint8_t g_rbuf[260];
/*********************************************************
函数名: void SPI1_Pins_Init(void)
描  述: SPI主机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void SPI1_Pins_Init(void)
{
    GPIO_InitSettingType x;

    /* 初始化SPI管脚 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(SPI_NSS, &x);

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(SPI_MOSI, &x);

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func1;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(SPI_MISO, &x);

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(SPI_SCK, &x);
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
    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_FallSendRiseRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                  
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         

    SPI1_Enable(); 

    SPI1_Pins_Init();
}
