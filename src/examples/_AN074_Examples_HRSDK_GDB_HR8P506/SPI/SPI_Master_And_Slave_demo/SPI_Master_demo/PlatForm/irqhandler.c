#include "irqhandler.h"

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
    TimingDelay_Decrement();
}

/*********************************************************
函数名: void SPI1_IRQHandler(void)
描  述: SPI中断处理程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPI1_IRQHandler(void)
{
    if ((SET == SPI_GetITStatus(SPI1, SPI_IT_RB)) && (SET == SPI_GetFlagStatus(SPI1, SPI_Flag_RB)))
    {
        g_rbuf[rbufIndex++] = SPI_RecByte(SPI1);

        if (rbufIndex == g_rbufamount)
        {
            SPI_ITConfig(SPI1, SPI_IT_RB, Disable);
        }
    }

    if ((SET == SPI_GetITStatus(SPI1, SPI_IT_TB)) && (SET == SPI_GetFlagStatus(SPI1, SPI_Flag_TB)))
    {
        SPI_SendByte(SPI1, g_wbuf[wbufIndex++]);

        if (wbufIndex == g_wbufamount)
        {
            SPI_ITConfig(SPI1, SPI_IT_TB, Disable);
        }
    }
}
