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
函数名: void T16N3_IRQHandler(void)
描  述: T16N3中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_CAP0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_CAP0);
        buf00[count00]  = T16N3->MAT0.Word;
        buf00[count00 + 1]  = T16N3->MAT2.Word;
        count00++;

        if (count00 >= 50)
        {
            count00 = 0;
        }
    }
}
