#include "irqhandler.h"
#include "lib_wdt.h"
extern uint8_t g_sleep_flag;
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
        SCU_RegUnLock();
        SCU_LVDClearIFBit();
        SCU_RegLock();
        g_sleep_flag = 1;
    }
}
