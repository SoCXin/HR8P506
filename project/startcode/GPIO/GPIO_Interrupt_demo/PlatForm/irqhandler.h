#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"

extern uint32_t SysCount;

extern uint8_t g_2ms_flag;
extern uint8_t g_2ms_cnt;
extern uint8_t g_1s_flag;
extern uint32_t g_1s_cnt;

extern uint8_t g_key_flag;

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
