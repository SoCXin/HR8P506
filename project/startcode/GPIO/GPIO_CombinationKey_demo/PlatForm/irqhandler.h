#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"

extern uint32_t SysCount;

extern uint8_t g_10ms_flag;
extern uint8_t g_200ms_flag;
extern uint8_t g_200ms_cnt;

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
