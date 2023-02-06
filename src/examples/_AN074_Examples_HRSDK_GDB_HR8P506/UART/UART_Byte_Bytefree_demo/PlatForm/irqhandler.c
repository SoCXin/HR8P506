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
extern uint8_t recv_finish;
/*********************************************************
函数名: void UART0_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void UART0_IRQHandler(void)
{
    if ((UART_GetFlagStatus(UART0, UART_FLAG_ID) != RESET))
    {
        UART_ClearITPendingBit(UART0, UART_FLAG_ID);
        recv_finish = 1;
    }

    if ((UART_GetITStatus(UART0, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET))
    {
        g_rxbuf = UART_RecByte(UART0);
    }
}
