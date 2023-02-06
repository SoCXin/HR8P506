#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "systick.h"


extern uint8_t g_txbuf[0xFF];          /* 发送数据缓存 */
extern uint8_t g_tx_length;            /* 发送数据长度 */
extern uint8_t g_tx_count;             /* 发送字节计数 */

extern uint8_t g_rxbuf[0xFF];          /* 接收数据缓存 */
extern uint8_t g_rx_length;            /* 接收数据长度 */
extern uint8_t g_rx_count;             /* 接收字节计数 */


/************中断函数声明***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
