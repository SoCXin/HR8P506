#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_config.h"
#include "light.h"
#include "systick.h"

uint8_t g_rxbuf;
//uint8_t g_recv_flag;

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
    TimingDelay_Decrement();
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
    if ((UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET) && (UART_GetITStatus(UART0, UART_IT_RB) != RESET))
    {
        g_rxbuf = UART_RecByte(UART0);

        if (g_rxbuf == 0x55)
        {
            g_recv_flag = 1;
            GPIO_SetBit(GPIO_Pin_A6);
            Delay_100us(500);
        }
    }
}
