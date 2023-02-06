/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  flash.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/14
*描  述:  FLASH模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "e2rom.h"
#include "spi.h"
#include "uart.h"
#include "string.h"

#define CS_EN()  GPIO_SetBit(SPI_NSS)
#define CS_DIS() GPIO_ResetBit(SPI_NSS)

/*********************************************************
函数名: void e2rom_DO_Init(void);
描  述: 初始化e2rom的DO管脚为普通IO
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void e2rom_DO_Init(void)
{
    GPIO_InitSettingType x;

    /* MISO Pin设置为GPIO，用于判断相应 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(SPI_MISO, &x);
}

/*********************************************************
函数名: void e2rom_DO_DefaultInit(void);
描  述: 初始化e2rom的DO管脚为SPI1的MISO
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void e2rom_DO_DefaultInit(void)
{
    GPIO_InitSettingType x;

    /* MISO Pin设置为GPIO，用于判断相应 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func1;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(SPI_MISO, &x);
}

/*********************************************************
函数名: void E2rom_Ewen(void)
描  述: EEPROM写使能
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void E2rom_Ewen(void)
{
    CS_EN();
	
    SPI_SendByte(SPI1, 0x02);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x60);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    CS_DIS();
}

/*********************************************************
函数名: void E2rom_Ewds(void)
描  述: EEPROM写禁止
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void E2rom_Ewds(void)
{
    CS_EN();
	
    SPI_SendByte(SPI1, 0x02);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x00);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    CS_DIS();
}

/*********************************************************
函数名: void E2rom_init(void)
描  述: 初始化E2ROM模块
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void E2rom_init(void)
{
    SPI1Init();
    UARTInit();
}

/*********************************************************
函数名: void E2romReadData(uint8_t addr, uint8_t *buf)
描  述: SPI读数据，连续字节读出(查询模式)
输入值: addr—地址
输出值: buf—接收数据缓存
返回值: 无
**********************************************************/
void E2romReadData(uint8_t addr, uint8_t *buf)
{
    CS_EN();
	
    SPI_SendByte(SPI1, 0x03);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, addr);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI1_RecEnable();

    while (SPI_GetFlagStatus(SPI1, SPI_Flag_RB));
    SPI_SendByte(SPI1, 0);
    while (SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == RESET);
    *buf = SPI_RecByte(SPI1);

    CS_DIS();

    SPI1_RecDisable();
}

/*********************************************************
函数名: void E2romWriteData(uint8_t addr, uint8_t buf)
描  述: E2rom写数据，逐个字节编程
输入值: addr—地址
        buf—待发送数据
输出值: 无
返回值: 无
**********************************************************/
void E2romWriteData(uint8_t addr, uint8_t buf)
{  
    e2rom_DO_Init();

    E2rom_Ewen();
    Delay_10us(1);

    CS_EN();

    SPI_SendByte(SPI1, 0x02);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x80 | addr);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, buf);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    CS_DIS();
    CS_EN();

    while ((GPIO_ReadBit(SPI_MISO)) == 0);

    CS_DIS();

    e2rom_DO_DefaultInit();

    Delay_10us(1);
    E2rom_Ewds(); 
}

/*********************************************************
函数名: void E2romEraseAll(void)
描  述: E2ROM擦除全片（填充0xFF）
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void E2romEraseAll(void)
{
    e2rom_DO_Init();

    E2rom_Ewen();
    Delay_10us(10);

    CS_EN();
	
    SPI_SendByte(SPI1, 0x02);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x40);
    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    CS_DIS();
    CS_DIS();
    CS_EN();

    while ((GPIO_ReadBit(SPI_MISO)) == 0);

    CS_DIS();

    e2rom_DO_DefaultInit();

    Delay_10us(10);
    E2rom_Ewds();
}
