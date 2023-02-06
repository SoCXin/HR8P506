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
#define ISR 1

uint8_t g_wbuf[20];
uint8_t g_rbuf[20];
uint8_t g_rbufamount;
uint8_t g_wbufamount;

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
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A2, &x);                /* NSS   - PA2，主控模式不支持硬件片选 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func3;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A5, &x);                /* MOSI  - PA5 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func3;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A3, &x);                /* SCK   - PA3 */

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func3;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A4, &x);                /* MISO  - PA4 */
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
    y.SPI_Freq = 1000000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;                              /* 位宽:7+1位 */
    y.SPI_DelayRec = Enable;                   /* 延时半周期 */
    y.SPI_DelaySend = Disable;                 /* 失能间隔发送 */
    y.SPI_SendDelayPeroid = 0x3F;              /* 间隔发送周期:64*Tsck */
    SPI_Init(SPI1, &y);

    SPI1_Pins_Init();
    GPIO_SetBit(GPIO_Pin_A2);                   /* NSS拉高 */
    SPI1_RecEnable();                           /* 使能SPI接收 */
	SPI_RBIMConfig(SPI1, SPI_IType_BYTE);
	SPI_TBIMConfig(SPI1, SPI_IType_BYTE);
    NVIC_Init(NVIC_SPI1_IRQn, NVIC_Priority_0, Enable);
    SPI1_Enable();
}

/*********************************************************
函数名: SPIReadData(uint8_t *rbuf, uint8_t n)
描  述: SPI读数据，连续字节读出(查询模式)
输入值: n—接收数据个数
输出值: rbuf—接收数据缓存
返回值: 无
**********************************************************/
void SPIReadData(uint8_t *rbuf, uint8_t n)
{
    uint8_t i;

    /*清空接收缓冲器*/
    rbufIndex = 0x0U;
    g_rbufamount = n;
    Clear_RBR(SPI1);
    Clear_TBW(SPI1);

#if ISR
    SPI_ITConfig(SPI1, SPI_IT_TB, Disable);
    SPI_ITConfig(SPI1, SPI_IT_RB, Enable);
#endif

    /*拉低片选*/
    GPIO_ResetBit(GPIO_Pin_A2);

    for (i = 0; i < n; i++)
    {
        while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        SPI_SendByte(SPI1, 0x3F);

#if ISR
#else

        while ((SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == RESET));

        g_rbuf[i] = SPI_RecByte(SPI1);
#endif
    }

#if ISR

    while (rbufIndex < n)
    {
        ;
    }

#endif

    GPIO_SetBit(GPIO_Pin_A2);

    memcpy(rbuf, g_rbuf, n);

    return;
}

/*********************************************************
函数名: SPIWriteData(uint8_t *wbuf, uint8_t n)
描  述: SPI写数据，连续字节读出
输入值: wbuf-发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
**********************************************************/
void SPIWriteData(uint8_t *wbuf, uint8_t n)
{
#if ISR
#else
    uint8_t i;
#endif

    /* 清空发送缓冲器 */
    wbufIndex = 0x0U;
    g_wbufamount = n;
    memcpy(g_wbuf, wbuf, n);
    Clear_TBW(SPI1);

    /* 拉低片选 */
    GPIO_ResetBit(GPIO_Pin_A2);

#if ISR
    SPI_ITConfig(SPI1, SPI_IT_TB, Enable);
    SPI_ITConfig(SPI1, SPI_IT_RB, Disable);
#endif

#if ISR
#else

    for (i = 0; i < n; i++)
    {
        SPI_SendByte(SPI1, wbuf[i]);

        while ((SPI_GetFlagStatus(SPI1, SPI_Flag_TB) == RESET) || SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    }

#endif

#if ISR

    while (wbufIndex < n)
    {
        ;
    }

#endif

	/* 等待发送空闲 */
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    GPIO_SetBit(GPIO_Pin_A2);

    return;
}
