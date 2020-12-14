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

uint32_t count0 = 0;
uint32_t count1 = 0;
uint32_t count2 = 0;
uint32_t count3 = 0;
/*********************************************************
������: void T16N0_IRQHandler(void)
��  ��: T16N0�жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N0_IRQHandler(void)
{
    count0++;

    if ((count0 % 100) < 50)                /* ��ʱ50�ε���LED */
        GPIO_WriteBit(GPIO_Pin_A6, 0);
    else
        GPIO_WriteBit(GPIO_Pin_A6, 1);

    count0 = count0 % 100;
}

/*********************************************************
������: void T16N1_IRQHandler(void)
��  ��: T16N1�жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N1_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N1, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N1, T16Nx_IT_MAT0);

        count1++;

        if ((count1 % 200) < 100)               /* ��ʱ100�ε���LED */
            GPIO_WriteBit(GPIO_Pin_A7, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A7, 1);

        count1 = count1 % 200;
    }
}

/*********************************************************
������: void T16N2_IRQHandler(void)
��  ��: T16N2�жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N2_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N2, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N2, T16Nx_IT_MAT0);

        count2++;

        if ((count2 % 300) < 150)            /* ��ʱ150�ε���LED */
            GPIO_WriteBit(GPIO_Pin_A8, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A8, 1);

        count2 = count2 % 300;
    }
}

/*********************************************************
������: void T16N3_IRQHandler(void)
��  ��: T16N3�жϴ�����
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);

        count3++;

        if ((count3 % 400) < 200)            /* ��ʱ200�ε���LED */
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A9, 1);

        count3 = count3 % 400;
    }
}

