#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "string.h"

extern uint8_t g_wbuf[8];
extern uint8_t g_rbuf[8];
uint32_t recv_cnt;
uint32_t send_cnt;

union byteconvert_t
{
    uint8_t  u8data[4];
    uint16_t u16data;
    uint32_t u32data;
} byteconv;

/************中断函数声明***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
