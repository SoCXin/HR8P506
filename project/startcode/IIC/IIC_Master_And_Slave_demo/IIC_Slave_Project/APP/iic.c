/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC�ӻ�ģ�����
*��  ע:  ������HRSDK-GDB-ES8P508 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "iic.h"


/*********************************************************
������: void IIC1MasterInit(void)
��  ��: IIC������ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void I2C0_SlaveInit(void)
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
    GPIO_Init(GPIO_Pin_B3, &x);    //PB3--SDA
    GPIO_Init(GPIO_Pin_B2, &x);    //PB2--SCL

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 10000;        //10KHz
    y.IIC_Mode = IIC_Mode_Slave;
    y.IIC_AutoStop = Disable;
    y.IIC_AutoCall = Disable;
    IIC_Init(I2C0, &y);

    IIC0_CSEnable();        //�Զ�����ʹ�ܣ��ڸ��ٴ����б���ʹ���Զ�����
    IIC_SetAddress(I2C0, SLAVE_ADDR);
    IIC_ITConfig(I2C0, IIC_IT_SR, Enable);
    IIC_ITConfig(I2C0, IIC_IT_SP, Enable);
    NVIC_Init(NVIC_IIC0_IRQn, NVIC_Priority_0, Enable);

    IIC0_Enable();
}

/*********************************************************
������: void IIC0_Init(void)
��  ��: IIC�ӻ���ʼ���ӳ�����λ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void I2C0_Init(void)
{
    IIC_InitStruType y;

    y.IIC_SckOd = IIC_PinMode_OD;
    y.IIC_SdaOd = IIC_PinMode_OD;
    y.IIC_16XSamp = Disable;
    y.IIC_Clk = 10000;        //10KHz
    y.IIC_Mode = IIC_Mode_Slave;
    y.IIC_AutoStop = Disable;
    y.IIC_AutoCall = Disable;
    IIC_Init(I2C0, &y);


    IIC_ITConfig(I2C0, IIC_IT_SR, Enable);
    IIC_ITConfig(I2C0, IIC_IT_SP, Enable);
    IIC0_Enable();
}

