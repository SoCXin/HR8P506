#include "irqhandler.h"
#include "lib_wdt.h"
#include "systick.h"

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
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_Disable(T16N3);
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);
        g_2ms_flag = 1;

        g_10ms_cnt++;

        if (g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }

        g_rx_time++;                        //累加接收计时

        if (g_rx_time >= INTERVAL_TIME)     //2ms*INTERVAL_TIME，超过最小帧间间隔时间，则表明一帧接收完
        {
            g_rx_time = 0;                  //清零UART通讯计时

            if (g_rx_start_flag == 1)       //判断接收起始标志
            {
                g_rx_start_flag = 0;        //清接收起始标志
                g_rx_finish_flag = 1;       //置接收完成标志
            }
            else
            {
                g_rx_finish_flag = 0;       //清接收完成标志
            }
        }

        T16Nx_Enable(T16N3);
    }

    return;
}

/*********************************************************
函数名: void UART0_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void UART0_IRQHandler(void)
{
    if ((UART_GetITStatus(UART0, UART_IT_TB) != RESET)
            && (UART_GetFlagStatus(UART0, UART_FLAG_TB) != RESET))//需要同时判断
    {
        UART_SendByte(UART0, g_txbuf[g_tx_count]);
        g_tx_count++;

        if (g_tx_count >= g_tx_length)
        {
            g_tx_count = 0;
            UART_ITConfig(UART0, UART_IT_TB, Disable);
        }
    }

    if ((UART_GetITStatus(UART0, UART_IT_RB) != RESET)
            && (UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET))//需要同时判断
    {
        g_rxbuf[g_rx_count] = UART_RecByte(UART0);
        g_rx_count++;

        if (g_rx_count >= 6)            //按通信协议，至少包含6个字节
            g_rx_start_flag = 1;        //置接收起始标志

        g_rx_time = 0;                  //清零UART通讯计时，表明仍处于数据帧接收过程
    }
}
