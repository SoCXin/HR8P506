#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"

extern uint32_t SysCount;
extern uint8_t g_recv_flag;
//extern uint8_t g_rxbuf;

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
