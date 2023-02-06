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

extern uint32_t count;
/*********************************************************
函数名: void T32N0_IRQHandler(void)
描  述: T32N0中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32N0_IRQHandler(void)
{
    if (T32Nx_GetFlagStatus(T32N0, T32Nx_IT_MAT0) != RESET)
    {
        T32Nx_ClearITPendingBit(T32N0, T32Nx_IT_MAT0);
        count++;

        if ((count % 2) == 1)
        {
            GPIO_WriteBit(GPIO_Pin_A6, 1);
            GPIO_WriteBit(GPIO_Pin_A7, 1);
            GPIO_WriteBit(GPIO_Pin_A8, 1);
            GPIO_WriteBit(GPIO_Pin_A9, 1);
        }
        else
        {
            GPIO_WriteBit(GPIO_Pin_A6, 0);
            GPIO_WriteBit(GPIO_Pin_A7, 0);
            GPIO_WriteBit(GPIO_Pin_A8, 0);
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        }
    }
}
