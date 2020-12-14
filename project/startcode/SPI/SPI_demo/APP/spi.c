/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  SPI主机模块程序
          访问EEPROM
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"

/*********************************************************
函数名: void SPIInit(void)
描  述: SPI主机初始化子程序
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
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A24, &x);                //DO  - PA24
    GPIO_Init(GPIO_Pin_A25, &x);                //DI  - PA25
    GPIO_Init(GPIO_Pin_A26, &x);                //CLK - PA26

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A27, &x);                //CS  - PA27

    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_FallSendRiseRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                   //延时半周期
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         //按照结构体的参数配置SPI

    SPI1_Enable();                              //使能SPI
}

/*********************************************************
函数名: void SPI0_Ewen(void)
描  述: EEPROM写使能
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1_Ewen(void)
{
    GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
    SPI_SendByte(SPI1, 0x02);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI_SendByte(SPI1, 0x60);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    GPIO_WriteBit(GPIO_Pin_A27, 0);
}

/*********************************************************
函数名: void SPI0_Ewen(void)
描  述: EEPROM写禁止
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1_Ewds(void)
{
    GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
    SPI_SendByte(SPI1, 0x02);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI_SendByte(SPI1, 0x00);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    GPIO_WriteBit(GPIO_Pin_A27, 0);
}

/*********************************************************
函数名: void SPIReadData(uchar addr, uchar *buf, uchar n)
描  述: SPI读数据，连续字节读出(查询模式)
输入值: addr—地址
        n—接收数据个数
输出值: buf—接收数据缓存
返回值: 无
**********************************************************/
void SPI1ReadData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;

    GPIO_WriteBit(GPIO_Pin_A27, 1);                     //CS
    SPI_SendByte(SPI1, 0x03);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI_SendByte(SPI1, addr);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI1_RecEnable();                                   //使能接收

    for (i = 0; i < n; i++)                             //接收
    {
        while (SPI_GetFlagStatus(SPI1, SPI_Flag_RB));   //缓存器空时才接收

        SPI_SendByte(SPI1, 0);                          //发送接收用的时钟

        while (SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == RESET);

        buf[i] = SPI_RecByte(SPI1);
    }

    GPIO_WriteBit(GPIO_Pin_A27, 0);                     //cs

    SPI1_RecDisable();                                  //禁止接收
}

/*********************************************************
函数名: uchar SPIWriteData(uchar memory_addr, uchar *buf, uchar n)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
**********************************************************/
void SPI1WriteData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A25, &x);            //MISO设为输入，用来判断响应

    SPI1_Ewen();                            //dis写保护
    Delay_100us(1);

    for (i = 0; i < n; i++)
    {
        GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
        SPI_SendByte(SPI1, 0x02);

        while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        SPI_SendByte(SPI1, 0x80 | (addr + i));

        while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        SPI_SendByte(SPI1, buf[i]);

        while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
        GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS

        while ((GPIO_ReadBit(GPIO_Pin_A25)) == 0); //等到MISO被拉高

        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
    }

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A25, &x);        //DI  - PA25

    Delay_100us(1);
    SPI1_Ewds();                            //写保护
}

/*********************************************************
函数名: void SPI0EraseAll(void)
描  述: SPI擦除全片（填充0xFF）
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1EraseAll(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir  = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE  = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A25, &x);            //MISO设为输入，用来判断响应

    SPI1_Ewen();                            //dis写保护
    Delay_100us(1);

    GPIO_WriteBit(GPIO_Pin_A27, 1);         //CS
    SPI_SendByte(SPI1, 0x02);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI_SendByte(SPI1, 0x40);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    GPIO_WriteBit(GPIO_Pin_A27, 0);         //CS
    GPIO_WriteBit(GPIO_Pin_A27, 0);         //CS
    GPIO_WriteBit(GPIO_Pin_A27, 1);         //CS

    while ((GPIO_ReadBit(GPIO_Pin_A25)) == 0); //等到MISO被拉高

    GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS


    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A25, &x);        //DI  - PA25

    Delay_100us(1);
    SPI1_Ewds();                            //写保护
}
