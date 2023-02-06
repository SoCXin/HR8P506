#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"

extern uint32_t SysCount;

extern uint8_t g_2ms_flag;
extern uint8_t g_2ms_cnt;
extern uint8_t g_10ms_flag;
extern uint8_t g_10ms_cnt;
extern uint8_t g_500ms_flag;
extern uint8_t g_500ms_cnt;

extern uint8_t g_sec_flag;
extern uint8_t g_min_flag;
extern uint8_t g_hour_flag;
extern uint8_t g_day_flag;
extern uint8_t g_month_flag;

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
