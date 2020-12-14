/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  506主机从机通信demo，本程序为从机程序，负责接收数据和发送上一次接收的数据。
        主机从机需要连接SCL（PB2）和SDA（PB3），并上拉。
*备  注:   V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "iic.h"
#include "system_HR8P506.h"



int main()
{
    SystemInit();                   //配置时钟
    DeviceClockAllEnable();         //打开所有外设时钟
    I2C0_SlaveInit();

    while (1)
    {

    }

}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
                 用户需要高速传输时，尽量使用操作寄存器的方法
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
unsigned char iic_buf[8];
unsigned char buf_count = 0;
void I2C0_IRQHandler(void)
{
    if (IIC_GetITStatus(I2C0, IIC_IT_SR) == SET) //收到起始位+地址匹配+发送应答位
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);            //清I2C起始位+地址匹配+发送应答位标志位

        if (IIC_GetRWMode(I2C0) == IIC_Mode_Read) //主机读
        {
            IIC_ITConfig(I2C0, IIC_IT_RB, Disable);

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_TIDLE, Enable);
            buf_count = 0;

            IIC_SendByte(I2C0, iic_buf[buf_count++]);       //写发送缓冲器，首字节
        }
        else if (IIC_GetRWMode(I2C0) == IIC_Mode_Write) //主机写
        {
            IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
            IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
            buf_count = 0;
        }
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_RB) == SET) //I2C接收缓冲器有接收数据
    {
        iic_buf[buf_count++] = IIC_RecByte(I2C0); //读接收缓冲器，硬件清接收中断标志
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_TIDLE) == SET) //I2C空闲
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);

        if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) != SET) //没有接收到NACK
        {
            IIC_SendByte(I2C0, iic_buf[buf_count++]);       //写发送缓冲器
        }
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_SP) == SET) //收到结束位
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);            //清结束位中断标志
        IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
        IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
        IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
        buf_count = 0;
    }
}




