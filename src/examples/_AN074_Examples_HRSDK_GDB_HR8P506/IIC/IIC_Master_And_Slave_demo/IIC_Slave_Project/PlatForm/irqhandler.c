#include "irqhandler.h"


/***************************************************************
***************************************************************/
uint8_t rxcnt;
uint8_t txcnt;


/***************************************************************
***************************************************************/
void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1)
    {
    }
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{

}


/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
         用户需要高速传输时，尽量使用操作寄存器的方法
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{
    /* 收到起始位+地址匹配+发送应答位 */
    if (IIC_GetITStatus(I2C0, IIC_IT_SR) == SET)
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

        if (IIC_GetRWMode(I2C0) == IIC_Mode_Read)
        {
            txcnt = 0x0U;

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
            IIC_ITConfig(I2C0, IIC_IT_TB, Enable);
        }
        else if (IIC_GetRWMode(I2C0) == IIC_Mode_Write)
        {
            rxcnt = 0x0U;

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
            IIC_ITConfig(I2C0, IIC_IT_TB, Disable);
        }
    }

    /* 接收中断 */
    if (IIC_GetITStatus(I2C0, IIC_IT_RB) == SET)
    {
        g_buf[rxcnt++] = IIC_RecByte(I2C0);
    }

    /* 发送中断 */
    if (IIC_GetITStatus(I2C0, IIC_IT_TB) == SET)
    {
        if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) != SET)
        {
            IIC_SendByte(I2C0, g_buf[txcnt++]);
        }
    }

    /* 收到结束位 */
    if (IIC_GetITStatus(I2C0, IIC_IT_SP) == SET) 
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
        IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

        IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
        IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
    }
}
