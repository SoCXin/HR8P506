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


uint8_t g_txbuf[255];
uint8_t g_rxbuf[255] ; 
uint8_t g_tx_length;
uint8_t g_rx_length;
volatile uint8_t g_tx_count;
volatile uint8_t g_rx_count;


/*********************************************************
函数名: void IIC1MasterInit(void)
描  述: IIC主机初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
static void IICMasterInit(void)
{
    IIC_InitStruType y;

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 100000;        			/* 100KHz */
    y.IIC_Mode = IIC_Mode_Master;
    y.IIC_AutoStop = Disable;
    y.IIC_AutoCall = Disable;
    IIC_Init(I2C0, &y);

    IIC_TBIMConfig(I2C0, IIC_TRBIM_Byte);
    IIC_RBIMConfig(I2C0, IIC_TRBIM_Byte);
    IIC_RecModeConfig(I2C0, IIC_RecMode_0);

	IIC_AckDelay(I2C0, IIC_AckDelay_4, Enable);
    NVIC_Init(NVIC_IIC0_IRQn, NVIC_Priority_1, Enable);
    IIC0_Enable();
}

/*********************************************************
函数名: void IICMasterInitPins(void)
描  述: IIC主机通信管脚初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void IICMasterInitPins(void)
{
    GPIO_InitSettingType x;

    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Output;		
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    x.ODE = GPIO_ODE_Output_Enable; 
    x.DS = GPIO_DS_Output_Strong;
    x.Signal = GPIO_Pin_Signal_Digital;	 
    GPIO_Init(GPIO_Pin_A4, &x);    		/* PA4 - SCL */
    GPIO_Init(GPIO_Pin_A5, &x);    		/* PA5 - SDA */
}

/*********************************************************
函数名: uint8_t IICReadByte(uint8_t slave_addr)
描  述: IIC读数据，连续字节读出
输入值: addr—地址
输出值: 无
返回值: buf—接收数据缓存
**********************************************************/
uint8_t IICReadByte(uint8_t slave_addr)
{
	uint32_t time_count = 0x0U;
    g_rx_length = 1;
    g_rx_count = 0;

	/* I2C主机配置初始化 */
	IICMasterInit();
	
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
	IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);
	
	IIC_RecModeConfig(I2C0, IIC_RecMode_1);
    IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
	IIC0_RDTrigger();
	
	/* 等待接收完成 */
	time_count = 0x0U;
    while ((g_rx_count < g_rx_length) && (++time_count < 0xFFF));

	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
	IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
	
	/* 复位I2C模块 */
	IIC0_Reset();
	
	return g_rxbuf[0];
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
    g_txbuf[0] = buf;
    g_tx_length = 1;
    g_tx_count = 0;
	
	/* I2C主机配置初始化 */
	IICMasterInit();
    IIC_ITConfig(I2C0, IIC_IT_TB, Enable); 
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
	
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

	/* 等待发送空闲 */
	time_count = 0x0U;
	while ((((IIC_GetTBStatus(I2C0) == RESET) || (g_tx_count != g_tx_length))) && (++time_count < 0xFFF));

	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));
    IIC0_SPTrigger();
	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
	
	/* 复位I2C模块 */
	IIC0_Reset();
	
    if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) == SET)
    {
        return ERROR;
    }

    return SUCCESS;
}

/*********************************************************
函数名: void IICReadBuf(uint8_t slave_addr, uint8_t *buf, uint8_t len)
描  述: IIC读数据，连续字节读出
输入值: addr—地址
        len-读取数据大小
输出值: 无
返回值: buf—接收数据缓存
**********************************************************/
void IICReadBuf(uint8_t slave_addr, uint8_t *buf, uint8_t len)
{
	uint32_t time_count = 0x0U;
	g_rx_length = len;
    g_rx_count = 0;
	
	/* I2C主机配置初始化 */
	IICMasterInit();
	
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Read);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

    IIC_RecModeConfig(I2C0, IIC_RecMode_6);
    IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
	IIC0_RDTrigger();
	
	/* 等待接收完成 */
	time_count = 0x0U;
	while ((g_rx_count < g_rx_length) && (++time_count < 0xFFF));
	
	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
	
	/* 复位I2C模块 */
	IIC0_Reset();
	
	memcpy(buf, g_rxbuf, len);
	
	return;
}

/*********************************************************
函数名: ErrorStatus IICWriteBuf(uint8_t slave_addr, uint8_t *buf, uint8_t len)
描  述: IIC连续写数据
输入值: addr—地址
        buf—发送数据缓存
        len-发送数据大小
输出值: 无
返回值: SUCCESS/ERROR
**********************************************************/
ErrorStatus IICWriteBuf(uint8_t slave_addr, uint8_t *buf, uint8_t len)
{
	uint32_t time_count = 0x0U;
	
    memcpy(g_txbuf, buf, len);
    g_tx_length = len;
    g_tx_count = 0;
	
	/* I2C主机配置初始化 */
	IICMasterInit();
    IIC_ITConfig(I2C0, IIC_IT_TB, Enable); 
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
	
    IIC_SendAddress(I2C0, slave_addr, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

	/* 等待发送空闲 */
	time_count = 0x0U;
    while ((((IIC_GetTBStatus(I2C0) == RESET) || (g_tx_count != g_tx_length))) && (++time_count < 0xFFF));
	
	time_count = 0x0U;
    IIC0_SPTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SP) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
	
	/* 复位I2C模块 */
	IIC0_Reset();
	
    if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) == SET)
    {
        return ERROR;
    }

    return SUCCESS;
}
