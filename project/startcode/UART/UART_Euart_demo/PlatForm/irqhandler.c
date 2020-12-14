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
������: void EUART0_IRQHandler(void)
��  ��: UART�жϷ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void EUART0_IRQHandler(void)
{
    if ((EUART_GetITStatus(EUART_IT_RB) != RESET) && (EUART_GetFlagStatus(EUART_FLAG_RB) != RESET))
    {
        g_rxbuf = EUART_RecByte();
        EUART_SendByte(g_rxbuf);
    }
}
