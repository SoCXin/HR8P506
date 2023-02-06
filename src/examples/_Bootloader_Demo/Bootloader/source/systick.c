#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"

uint32_t  g_boot_timer;   //��ʱ���������ʱ��
uint32_t  g_frame_timer;  //֡�����ʱ��ʱ��
uint8_t   g_boot;  //���������ʶ

extern isp_data_t g_isp_data;

void uart0_reset(void);
void uart1_reset(void);
void uart2_reset(void);
void uart_init(UART_TypeDef *uartx);
/***************************************************************
��������SysTick_Handler
��  ��: SysTick�жϷ������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void SysTick_IRQHandler(void)
{
    if (GPIO->PAPORT.PORT_24 == 0) //BootPIN����
    {
        if (g_boot_timer != 0)
        {
            g_boot_timer--;

            if (g_boot_timer == 0)
            {
                g_boot = 1;  //��������
            }
        }
    }

    if (g_frame_timer != 0) //֡�ֽڼ��ʱ�䳬ʱ��λUART����ʹ�������½���ȴ��������״̬
    {
        g_frame_timer--;

        if (g_frame_timer == 0)
        {
            g_isp_data.step = WAIT_REV_INS;
            uart0_reset();
            uart_init(UART0);

        }
    }

}
