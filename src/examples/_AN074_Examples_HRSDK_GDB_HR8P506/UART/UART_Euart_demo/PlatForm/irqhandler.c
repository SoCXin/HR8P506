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
函数名: void EUART0_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void EUART0_IRQHandler(void)
{
    if ((EUART_GetITStatus(EUART_IT_RB) != RESET) && (EUART_GetFlagStatus(EUART_FLAG_RB) != RESET))
    {
        g_rxbuf = EUART_RecByte();
        EUART_SendByte(g_rxbuf);
    }
}
