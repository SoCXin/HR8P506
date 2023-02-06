#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "lib_config.h"
#include "HR8P506.h"

extern uint8_t g_buf[255];

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
