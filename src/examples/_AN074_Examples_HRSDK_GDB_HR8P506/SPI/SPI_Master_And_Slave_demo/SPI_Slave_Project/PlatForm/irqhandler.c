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
    if ((SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == SET) && (SPI_GetITStatus(SPI1, SPI_IT_RB) == SET))
    {
        g_rbuf[recv_cnt++] = SPI_RecByte(SPI1);
        memcpy(g_wbuf, g_rbuf, recv_cnt);

        if (recv_cnt > 7)
        {
            recv_cnt = 0;
        }
    }

    if ((SPI_GetFlagStatus(SPI1, SPI_Flag_TB) == SET) && (SPI_GetITStatus(SPI1, SPI_IT_TB) == SET))
    {
        SPI_SendByte(SPI1, g_wbuf[send_cnt++]);

        if (send_cnt > 7)
        {
            send_cnt = 0;
        }
    }
}
