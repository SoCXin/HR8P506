#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"

uint32_t count;

/***************************************************************
��������SysTick_Handler
��  ��: SysTick�жϷ������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void SysTick_IRQHandler(void)
{
    count++;

    if (count > 500)
    {
        count = 0;
        GPIO->PADATABRR.Word = 1U << 6;
    }
}
