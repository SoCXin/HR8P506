#include "irqhandler.h"
#include "lib_wdt.h"
#include "systick.h"

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

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}

/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3,T16Nx_IT_MAT0 )!= RESET)
    {
        T16Nx_ClearITPendingBit(T16N3,T16Nx_IT_MAT0);
        g_2ms_flag = 1;

        g_10ms_cnt++;
        if(g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }

        g_500ms_cnt++;
        if(g_500ms_cnt >= 250)
        {
            g_500ms_cnt = 0;
            g_500ms_flag = 1;
        }
    }

    return;
}

/*********************************************************
函数名: void I2C0_IRQHandler(void)
描  述: I2C0_IRQHandler中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void I2C0_IRQHandler(void)
{
    if((IIC_GetTBStatus(I2C0) != RESET) && IIC_GetITStatus(I2C0,IIC_IT_TB) == SET)
    {
        IIC_SendByte(I2C0, g_txbuf[g_tx_count]);
        g_tx_count++;
        if(g_tx_count >= g_tx_length)
        {
            g_tx_count = 0;
            IIC_ITConfig(I2C0,IIC_IT_TB,Disable);
        }
    }

    if(IIC_GetFlagStatus(I2C0,IIC_IF_RB) != RESET && IIC_GetITStatus(I2C0,IIC_IT_RB) == SET)
    {
        g_rxbuf[g_rx_count] = IIC_RecByte(I2C0);
        g_rx_count++;
    }
}


