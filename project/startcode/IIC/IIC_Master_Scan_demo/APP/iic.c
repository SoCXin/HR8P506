/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  IIC主机模块程序
          访问EEPROM
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "iic.h"

/*********************************************************
函数名: void IIC1MasterInit(void)
描  述: IIC主机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void IIC0_MasterInit(void)
{
    GPIO_InitSettingType x;
    IIC_InitStruType y;

    //IIC0  PB02 03
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func3;
    x.ODE = GPIO_ODE_Output_Enable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B2, &x);     //SCL  - PA24
    GPIO_Init(GPIO_Pin_B3, &x);     //SDA  - PA25

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 300000;        //300KHz
    y.IIC_Mode = IIC_Mode_Master;
    y.IIC_AutoStop = Disable;
    y.IIC_AutoCall = Disable;
    IIC_Init(I2C0, &y);

    IIC_TBIMConfig(I2C0, IIC_TRBIM_Byte);
    IIC_RBIMConfig(I2C0, IIC_TRBIM_Byte);
    IIC_RecModeConfig(I2C0, IIC_RecMode_0);

    IIC0_Enable();
}

/*********************************************************
函数名: uint8_t IIC1ReadByte(uint8_t slave_addr, uint8_t memory_addr)
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
输出值: 无
返回值: buf—接收数据缓存
**********************************************************/
uint8_t IIC0_ReadByte(uint8_t slave_addr, uint8_t memory_addr)
{
    uint8_t buf;

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC_SendByte(I2C0, memory_addr);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC0_RDTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET);

    buf = IIC_RecByte(I2C0);

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == SET);

    IIC0_SPTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET);

    return buf;
}

/*********************************************************
函数名: void IIC1MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
        n—接收数据个数
输出值: buf—接收数据缓存
返回值: 无
**********************************************************/
void IIC0_MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
{
    while (n--)
    {
        *buf = IIC0_ReadByte(slave_addr, memory_addr);
        memory_addr++;
        buf++;
    }
}

/*********************************************************
函数名: void IIC1WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
输出值: 无
返回值: 无
**********************************************************/
ErrorStatus IIC0_WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf)
{
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC_SendByte(I2C0, memory_addr);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC_SendByte(I2C0, buf);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC0_SPTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);

    if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) == SET)
    {
        return ERROR;
    }

    return SUCCESS;
}

/*********************************************************
函数名: void IIC1MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
**********************************************************/
void IIC0_MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
{
    while (n--)
    {
        IIC0_WriteByte(slave_addr, memory_addr, *buf);
        Delay_100us(100);
        memory_addr++;
        buf++;
    }
}

/*********************************************************
函数名: void IIC1MasterErasePage(uint8_t slave_addr, uint8_t memory_addr)
描  述: I2CM擦除页面（填充0xFF），8字节/页
输入值: slave_addr—从机地址
        memory_addr—片内地址
输出值: 无
返回值: 无
**********************************************************/
ErrorStatus IIC0_MasterErasePage(uint8_t slave_addr, uint8_t memory_addr)
{
    uint8_t i;
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    while (IIC_GetTBStatus(I2C0) == RESET);

    IIC_SendByte(I2C0, memory_addr);

    while (IIC_GetTBStatus(I2C0) == RESET);

    for (i = 0; i < 8; i++)
    {
        IIC_SendByte(I2C0, 0xFF);

        while (IIC_GetTBStatus(I2C0) == RESET);
    }

    IIC0_SPTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET);

    if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) == SET)
    {
        return ERROR;
    }

    return SUCCESS;
}
