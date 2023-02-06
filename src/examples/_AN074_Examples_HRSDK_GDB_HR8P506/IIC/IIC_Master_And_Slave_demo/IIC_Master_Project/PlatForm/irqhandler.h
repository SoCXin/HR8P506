#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "systick.h"


extern uint8_t g_txbuf[0xFF];          /* �������ݻ��� */
extern uint8_t g_tx_length;            /* �������ݳ��� */
extern uint8_t g_tx_count;             /* �����ֽڼ��� */

extern uint8_t g_rxbuf[0xFF];          /* �������ݻ��� */
extern uint8_t g_rx_length;            /* �������ݳ��� */
extern uint8_t g_rx_count;             /* �����ֽڼ��� */


/************�жϺ�������***********/
void  NMI_IRQHandler(void);
void  HardFault_IRQHandler(void);
void  SVC_IRQHandler(void);
void  PendSV_IRQHandler(void);
void  SysTick_IRQHandler(void);

#endif
