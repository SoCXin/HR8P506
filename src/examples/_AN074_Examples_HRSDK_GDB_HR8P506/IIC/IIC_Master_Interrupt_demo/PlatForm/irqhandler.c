#include "irqhandler.h"

void NMI_IRQHandler(void)
{
    
}

void HardFault_IRQHandler(void)
{
    while(1)
    {
    }
}

void SVC_IRQHandler(void)
{
    
}

void PendSV_IRQHandler(void)
{
    
}

/***************************************************************
 函数名: void SysTick_IRQHandler(void)
 描  述：systick中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{
	if((IIC_GetFlagStatus(I2C0, IIC_IF_TB) == SET) && IIC_GetITStatus(I2C0,IIC_IT_TB) == SET)
    {
        IIC_SendByte(I2C0, g_txbuf[g_tx_count++]);

        if(g_tx_count == g_tx_length)
        {
            IIC_ITConfig(I2C0,IIC_IT_TB,Disable);
        }
    }

    if(IIC_GetFlagStatus(I2C0,IIC_IF_RB) == SET && IIC_GetITStatus(I2C0,IIC_IT_RB) == SET)
    {
		/* 接收最后一个字节前需要将RDM配置为接收一字节发送NACK来正确结束接收过程 */
		if (g_rx_count == g_rx_length - 1)
		{
			IIC_RecModeConfig(I2C0, IIC_RecMode_1);
		}
		
		/* 必须每次都设置触发位，否则下次将不会进入中断 */
		IIC0_RDTrigger();
			
        g_rxbuf[g_rx_count++] = IIC_RecByte(I2C0);
		
		if (g_rx_count == g_rx_length)
		{
            IIC_ITConfig(I2C0,IIC_IT_RB,Disable);
        }
    }
}
