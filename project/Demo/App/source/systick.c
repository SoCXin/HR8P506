#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"

uint32_t count;

/***************************************************************
函数名：SysTick_Handler
描  述: SysTick中断服务程序
输入值：无
输出值：无
返回值：无
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
