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

/***************************************************************
 函数名: void SysTick_IRQHandler(void)
 描  述：systick中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{

}
