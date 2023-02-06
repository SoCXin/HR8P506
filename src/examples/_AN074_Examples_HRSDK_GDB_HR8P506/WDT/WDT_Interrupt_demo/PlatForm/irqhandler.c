#include "irqhandler.h"
#include "lib_wdt.h"

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

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}
void WDT_IRQHandler(void)
{
    WDT_Clear();                  //喂狗则不复位，不喂狗则复位
}
