#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_config.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1);
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
������: void UART0_IRQHandler(void)
��  ��: UART�жϷ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void UART0_IRQHandler(void)
{
    if ((UART_GetITStatus(UART0, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET))
    {
        g_rxbuf = UART_RecByte(UART0);
        UART_SendByte(UART0, g_rxbuf);
    }
}
