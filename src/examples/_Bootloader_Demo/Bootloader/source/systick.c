#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"

uint32_t  g_boot_timer;   //超时引导程序计时器
uint32_t  g_frame_timer;  //帧间隔超时计时器
uint8_t   g_boot;  //引导程序标识

extern isp_data_t g_isp_data;

void uart0_reset(void);
void uart1_reset(void);
void uart2_reset(void);
void uart_init(UART_TypeDef *uartx);
/***************************************************************
函数名：SysTick_Handler
描  述: SysTick中断服务程序
输入值：无
输出值：无
返回值：无
***************************************************************/
void SysTick_IRQHandler(void)
{
    if (GPIO->PAPORT.PORT_24 == 0) //BootPIN拉低
    {
        if (g_boot_timer != 0)
        {
            g_boot_timer--;

            if (g_boot_timer == 0)
            {
                g_boot = 1;  //引导程序
            }
        }
    }

    if (g_frame_timer != 0) //帧字节间隔时间超时则复位UART，并使命令重新进入等待命令码的状态
    {
        g_frame_timer--;

        if (g_frame_timer == 0)
        {
            g_isp_data.step = WAIT_REV_INS;
            uart0_reset();
            uart_init(UART0);

        }
    }

}
