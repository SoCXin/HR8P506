/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2018/07/04
*��  ��:  Bootloader��ʾ����

          RX��PA22  TX��PA23  BootPin��PA24
          �����ʣ�����Ӧ  У��λ��żУ��  ֹͣλ��1λ
          ��ʾ������ο��ĵ� AN082_Ӧ�ñʼ�_ES8Pϵ��MCU bootloader
*��  ע:  ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "lib_flashiap.h"

extern isp_data_t g_isp_data;
extern uint32_t  g_boot_timer;
extern uint8_t   g_boot;

void uart_init(UART_TypeDef *uartx);
void uart_proc_fsm(void);
void fsm_init(void);
void JumpToApp(uint32_t addr);
/***************************************************************
��������systick_init
��  ��: Systick��ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void systick_init(void)
{
    SysTick->CTRL = 0x07;
    SysTick->LOAD = 16000;  //ϵͳʱ��24M��1ms����һ���ж�
    SysTick->VAL = 0;
}

/***************************************************************
��������gpio_init
��  ��: GPIO��ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void gpio_init(void)
{
    SCU->PROT.Word = 0X55AA6996;
    SCU->PCLKEN.GPIO_EN = 1;
    SCU->PCLKEN.UART0_EN = 1;

    //BootPIN:PA24
    GPIO->PADIR.DIR_24 = 1; //����ر�
    GPIO->PAINEB.INEB_24 = 0; //�����
    GPIO->PAPDE.PDE_24 = 1; //��������
    GPIO->PAFUNC3.PA24 = 0;   //GPIO

    //RX:PA22
    GPIO->PADIR.DIR_22 = 1; //����ر�
    GPIO->PAINEB.INEB_22 = 0; //�����
    GPIO->PAFUNC2.PA22 = 1;   //FUNC1 RXD

    //TX:PA23
    GPIO->PADIR.DIR_23 = 0; //�����
    GPIO->PAINEB.INEB_23 = 1; //����ر�
    GPIO->PAFUNC2.PA23 = 1;   //FUNC1 TXD


}

int SystemInit(void)
{

    return 0;
}
/***************************************************************
��������main
��  ��: boot ������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
volatile uint32_t DATA;
int main(void)
{
    g_isp_data.syn = 0; //��δ�������
    gpio_init();
    uart_init(UART0);

    systick_init();
    fsm_init();  //״̬����ʼ��

    NVIC_EnableIRQ(UART0_IRQn);
    WDT->LOCK.Word = 0x1ACCE551;

    while (1)
    {
        WDT->INTCLR.Word = 0xFFFFFFFF; //�幷

        if (g_isp_data.triger == 1)
        {
            __disable_irq();  //�ٽ�δ��뱣��

            while (g_isp_data.triger == 1)
            {
                uart_proc_fsm();  //isp����״̬������
            }

            __enable_irq();
        }

        if (g_boot == 1) //��Ҫ��������flash
        {
            JumpToApp(APP_ADDR);
        }
    }
}
