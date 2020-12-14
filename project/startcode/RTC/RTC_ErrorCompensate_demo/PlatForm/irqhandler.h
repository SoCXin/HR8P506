
#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"


extern uint32_t SysCount;

/************中断函数声明***********/
void    Exception_NMI_IRQHandler(void);
void    Exception_HardFault_IRQHandler(void);
void    Exception_SVCall_IRQHandler(void);
void    Exception_PendSV_IRQHandler(void);
void    Exception_SysTick_IRQHandler(void);

void    EUART0_IRQHandler(void);       //EUART0中断（后来添加）

#endif
