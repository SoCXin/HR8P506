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
������: void T16N3_IRQHandler(void)
��  ��: T16N3��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
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

        g_rx_time++;                        //�ۼӽ��ռ�ʱ

        if (g_rx_time >= INTERVAL_TIME)     //2ms*INTERVAL_TIME��������С֡����ʱ�䣬�����һ֡������
        {
            g_rx_time = 0;                  //����UARTͨѶ��ʱ

            if (g_rx_start_flag == 1)       //�жϽ�����ʼ��־
            {
                g_rx_start_flag = 0;        //�������ʼ��־
                g_rx_finish_flag = 1;       //�ý�����ɱ�־
            }
            else
            {
                g_rx_finish_flag = 0;       //�������ɱ�־
            }
        }

        T16Nx_Enable(T16N3);
    }

    return;
}

/*********************************************************
������: void UART0_IRQHandler(void)
��  ��: UART�жϷ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void UART0_IRQHandler(void)
{
    if ((UART_GetITStatus(UART0, UART_IT_TB) != RESET)
            && (UART_GetFlagStatus(UART0, UART_FLAG_TB) != RESET))//��Ҫͬʱ�ж�
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
            && (UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET))//��Ҫͬʱ�ж�
    {
        g_rxbuf[g_rx_count] = UART_RecByte(UART0);
        g_rx_count++;

        if (g_rx_count >= 6)            //��ͨ��Э�飬���ٰ���6���ֽ�
            g_rx_start_flag = 1;        //�ý�����ʼ��־

        g_rx_time = 0;                  //����UARTͨѶ��ʱ�������Դ�������֡���չ���
    }
}
