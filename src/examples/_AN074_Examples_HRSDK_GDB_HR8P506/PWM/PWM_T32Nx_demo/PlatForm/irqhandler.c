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
extern unsigned int Period;
extern unsigned int dutytab[6];
extern unsigned int dutyindex;
extern unsigned int dutyNext;
/*********************************************************
函数名: void T32N0_IRQHandler(void)
描  述: T32N0中断处理函数 1000us
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32N0_IRQHandler(void)
{
    if (T32Nx_GetFlagStatus(T32N0, T32Nx_IT_MAT2) != RESET)
    {
        T32Nx_ClearITPendingBit(T32N0, T32Nx_IT_MAT2);

        if (dutyindex < 5)
            dutyindex++;
        else
            dutyindex = 0;

        T32Nx_SetMAT3(T32N0, dutytab[dutyindex]);

        if (dutytab[dutyindex] == 0)
            T32Nx_SetMAT3(T32N0, Period);

        if (dutyindex == 5)
            dutyNext = 0;
        else
            dutyNext = dutyindex + 1;

        if (dutytab[dutyNext] == 0)
            T32Nx_MAT2Out1Config(T32N0, T32Nx_Out_Low); //CNT0匹配到MAT1端口输出低
        else
            T32Nx_MAT2Out1Config(T32N0, T32Nx_Out_High); //CNT0匹配到MAT0端口输出高
    }
}
