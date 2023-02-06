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
extern uint32_t count00;
extern uint32_t buf00[50];
/*********************************************************
函数名: void T32N0_IRQHandler(void)
描  述: T32N0中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32N0_IRQHandler(void)
{
    if (T32Nx_GetFlagStatus(T32N0, T32Nx_IT_CAP0) != RESET)
    {
        T32Nx_ClearITPendingBit(T32N0, T32Nx_IT_CAP0);
        buf00[count00]  = T32N0->MAT0.Word;
        buf00[count00 + 1]  = T32N0->MAT2.Word;
        count00++;

        if (count00 >= 50)
        {
            count00 = 0;
        }
    }
}

