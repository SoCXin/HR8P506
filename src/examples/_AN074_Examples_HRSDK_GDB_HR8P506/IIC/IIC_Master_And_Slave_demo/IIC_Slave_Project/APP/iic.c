/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  IIC从机模块程序
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
void I2C0_SlaveInit(void)
{
    GPIO_InitSettingType x;
    IIC_InitStruType y;

    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Output;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.Signal = GPIO_Pin_Signal_Digital;
    GPIO_Init(GPIO_Pin_A5, &x);             /* PA05--SDA */
    GPIO_Init(GPIO_Pin_A4, &x);             /* PA04--SCL */

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 400000;
    y.IIC_Mode = IIC_Mode_Slave;
    y.IIC_AutoStop = Disable;
    y.IIC_AutoCall = Disable;
    IIC_Init(I2C0, &y);

    IIC0_CSEnable();                        /* 自动下拉使能，在高速传输中必须使能自动下拉 */
    IIC_SetAddress(I2C0, SLAVE_ADDR);

    IIC_ITConfig(I2C0, IIC_IT_SR, Enable);
    IIC_ITConfig(I2C0, IIC_IT_SP, Enable);
    NVIC_Init(NVIC_IIC0_IRQn, NVIC_Priority_0, Enable);

    IIC0_Enable();
}

