#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_config.h"

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
    //TimingDelay_Decrement();
}

/*********************************************************
������: void T16N3_IRQHandler(void)
��  ��: T16N3��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);
        g_2ms_flag = 1;

        g_1s_cnt++;

        if (g_1s_cnt >= 500)
        {
            g_1s_cnt = 0;
            g_1s_flag = 1;
        }
    }

    return;
}

/*********************************************************
������: void Interrupt_KINT_Handler(void)
��  ��: �����жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void KINT_IRQHandler(void)
{
    if (KINT_GetITFlag(GPIO_Pin_B9) != RESET)
    {
        KINT_ClearITFlag(GPIO_Pin_B9);      // ��������жϱ�־λ
        g_key_flag = 1;
    }
}


