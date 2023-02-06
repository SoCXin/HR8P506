#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "systick.h"


volatile extern uint8_t g_rx_count;
volatile extern uint8_t g_tx_count;
volatile extern uint8_t g_tx_finish;
extern uint8_t g_txbuf[255];
extern uint8_t g_tx_length;
extern uint8_t g_rxbuf[255] ; 
extern uint8_t g_rx_length;


/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
