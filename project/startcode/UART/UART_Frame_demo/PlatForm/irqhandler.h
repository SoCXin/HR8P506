#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"

#define INTERVAL_TIME 5        //通讯协议帧间最小间隔时间，字节间最大超时时间，单位2ms

extern uint32_t SysCount;

extern uint8_t g_2ms_flag;
extern uint8_t g_2ms_cnt;
extern uint8_t g_10ms_flag;
extern uint8_t g_10ms_cnt;
extern uint8_t g_500ms_flag;
extern uint8_t g_500ms_cnt;

extern uint8_t g_tx_length;
extern uint8_t g_tx_count;
extern uint8_t g_rx_length;
extern uint8_t g_rx_count;
extern uint8_t g_rx_finish_flag;
extern uint8_t g_rx_start_flag;
extern uint8_t g_rx_time;

extern uint8_t g_txbuf[0xFF];
extern uint8_t g_rxbuf[0xFF];

/************中断函数声明***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
