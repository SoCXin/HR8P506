#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"
#include "lib_config.h"


extern uint8_t g_wbuf[8];
extern uint8_t g_rbuf[16];
extern uint8_t g_rbufamount;
extern uint8_t g_wbufamount;

extern void TimingDelay_Decrement(void);


volatile uint8_t rbufIndex;
volatile uint8_t wbufIndex;

/************中断函数声明***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
