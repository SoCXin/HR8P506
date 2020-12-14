/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������
          ʹ��UART0��PA23���ͣ�ʹ��38KPWM���ƣ������շ�����������0x55,�����жϺ󣬽����յ�0x55���ͣ����ָʾ
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "systick.h"

extern uint8_t g_rxbuf;

int main(void)
{
    SystemInit();                //����ʱ��
    DeviceClockAllEnable();      //����������ʱ��

    User_SysTickInit();
    LightInit();
    UARTInit();                         //UART��ʼ��(1200,8,NO,1)

    g_recv_flag = 0;

    GPIO_SetBit(GPIO_Pin_A6);
    GPIO_SetBit(GPIO_Pin_A7);
    GPIO_SetBit(GPIO_Pin_A8);
    GPIO_SetBit(GPIO_Pin_A9);

    UART_SendByte(UART0, 0x55);

    while (1)
    {
        if (1 == g_recv_flag)
        {
            g_recv_flag = 0;
            g_rxbuf = 0;
            UART_SendByte(UART0, 0x55);
            GPIO_ResetBit(GPIO_Pin_A6);
            Delay_100us(500);
        }
    }
}



