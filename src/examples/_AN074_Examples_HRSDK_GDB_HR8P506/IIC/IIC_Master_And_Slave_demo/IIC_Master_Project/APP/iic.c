/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  IIC主机模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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

    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Output;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    x.ODE = GPIO_ODE_Output_Enable;
    x.DS = GPIO_DS_Output_Strong;
    x.Signal = GPIO_Pin_Signal_Digital;
    GPIO_Init(GPIO_Pin_A4, &x);         /* PA4 - SCL */
    GPIO_Init(GPIO_Pin_A5, &x);         /* PA5 - SDA */

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 400000;                 /* 400KHz */
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
	uint32_t time_count = 0x0U;
    uint8_t temp;
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC0_RDTrigger();

	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET) && (++time_count < 0xFFF));
    temp = IIC_RecByte(I2C0);
	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_RB) == SET) && (++time_count < 0xFFF));

	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);

    return temp;
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
	uint32_t time_count = 0x0U;
	
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));
    IIC_SendByte(I2C0, buf);
	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));

	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
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
void IICReadBuf(uint8_t slave_addr, uint8_t *buf, uint8_t size)
{
	uint32_t time_count = 0x0U;
	
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);
	
    IIC_RecModeConfig(I2C0, IIC_RecMode_6);          

    while (size-- > 1)
    {
        IIC0_RDTrigger();
		time_count = 0x0U;
        while ((IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET) && (++time_count < 0xFFF));
        *buf++ = IIC_RecByte(I2C0);
    }

    IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC0_RDTrigger();
	
	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_RB) == RESET) && (++time_count < 0xFFF));
    *buf = IIC_RecByte(I2C0);
	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_RB) == SET) && (++time_count < 0xFFF));

	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
	
	return;
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
ErrorStatus IICWriteBuf(uint8_t slave_addr, uint8_t *buf, uint8_t size)
{
	uint32_t time_count = 0x0U;
	
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    while (size-- > 0)
    {
		time_count = 0x0U;
        while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));
		time_count = 0x0U;
        IIC_SendByte(I2C0, *buf++);
		while ((IIC_GetFlagStatus(I2C0, IIC_IF_TB) == RESET) && (++time_count < 0xFFF));
    }

	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));

	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);


    if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) == SET)
    {
        return ERROR;
    }

    return SUCCESS;
}
