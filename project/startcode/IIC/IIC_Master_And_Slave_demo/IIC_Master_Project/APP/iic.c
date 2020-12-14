/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC主机模块程序
*备  注:   V1.0
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
void IICMasterInit(void)
{
    GPIO_InitSettingType x;
    IIC_InitStruType y;

    x.Func = GPIO_Reuse_Func3;
    x.Dir = GPIO_Direction_Output;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    x.ODE = GPIO_ODE_Output_Enable;
    x.DS = GPIO_DS_Output_Strong;
    x.Signal = GPIO_Pin_Signal_Digital;
    GPIO_Init(GPIO_Pin_B2, &x);    //PB2--SCL
    GPIO_Init(GPIO_Pin_B3, &x);    //PB3--SDA

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 10000;        //10KHz
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
函数名: uint8_t IICReadByte(uint8_t slave_addr)
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
输出值: 无
返回值: buf—接收数据缓存
**********************************************************/
uint8_t IICReadByte(uint8_t slave_addr)
{
    uint8_t i;

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC0_RDTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET);

    i = IIC_RecByte(I2C0);

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == SET);


    IIC0_SPTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);

    return i;
}

/*********************************************************
函数名: ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf)
描  述: IIC写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
输出值: 无
返回值: SUCCESS/ERROR
**********************************************************/
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf)
{
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

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
函数名: void IICReadBuf(uint8_t slave_addr , char * buf, char size )
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
        size-读取数据大小
输出值: 无
返回值: buf—接收数据缓存
**********************************************************/
void IICReadBuf(uint8_t slave_addr, char *buf, char size)
{

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    IIC_RecModeConfig(I2C0, IIC_RecMode_0);

    while (size-- > 1)
    {
        IIC0_RDTrigger();

        while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET);

        *buf++ = IIC_RecByte(I2C0);
    }

    IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC0_RDTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET);

    *buf = IIC_RecByte(I2C0);

    while (IIC_GetFlagStatus(I2C0, IIC_IF_RB) == SET);

    IIC0_SPTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
}




/*********************************************************
函数名: IICWriteBuf
描  述: IIC连续写数据
输入值: addr—地址
        buf—发送数据缓存
        size-发送数据大小
输出值: 无
返回值: SUCCESS/ERROR
**********************************************************/
ErrorStatus IICWriteBuf(uint8_t slave_addr, char *buf, char size)
{
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();

    while (IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET);

    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    while (size-- > 0)
    {
        while (IIC_GetTBStatus(I2C0) == RESET);

        IIC_SendByte(I2C0, *buf++);
    }

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
