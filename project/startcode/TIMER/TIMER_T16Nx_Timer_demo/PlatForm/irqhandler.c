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
函数名: void T16N0_IRQHandler(void)
描  述: T16N0中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N0_IRQHandler(void)
{
    count0++;

    if ((count0 % 100) < 50)                /* 超时50次点亮LED */
        GPIO_WriteBit(GPIO_Pin_A6, 0);
    else
        GPIO_WriteBit(GPIO_Pin_A6, 1);

    count0 = count0 % 100;
}

/*********************************************************
函数名: void T16N1_IRQHandler(void)
描  述: T16N1中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N1_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N1, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N1, T16Nx_IT_MAT0);

        count1++;

        if ((count1 % 200) < 100)               /* 超时100次点亮LED */
            GPIO_WriteBit(GPIO_Pin_A7, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A7, 1);

        count1 = count1 % 200;
    }
}

/*********************************************************
函数名: void T16N2_IRQHandler(void)
描  述: T16N2中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N2_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N2, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N2, T16Nx_IT_MAT0);

        count2++;

        if ((count2 % 300) < 150)            /* 超时150次点亮LED */
            GPIO_WriteBit(GPIO_Pin_A8, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A8, 1);

        count2 = count2 % 300;
    }
}

/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);

        count3++;

        if ((count3 % 400) < 200)            /* 超时200次点亮LED */
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        else
            GPIO_WriteBit(GPIO_Pin_A9, 1);

        count3 = count3 % 400;
    }
}

