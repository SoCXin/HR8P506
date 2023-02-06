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

void LVD_IRQHandler(void)
{
    if (SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)
    {
        SCU_LVDClearIFBit();

        GPIO_WriteBit(GPIO_Pin_A6, 0);
        GPIO_WriteBit(GPIO_Pin_A7, 0);
        GPIO_WriteBit(GPIO_Pin_A8, 0);
        GPIO_WriteBit(GPIO_Pin_A9, 0);
    }
}
