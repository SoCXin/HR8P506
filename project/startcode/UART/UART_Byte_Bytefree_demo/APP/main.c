/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������
            �Զ��������жϣ�����⵽����֡�󣬴����жϣ�����Byte��������ͬByte
*��  ע:  оƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t recv_finish = 0;

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    UARTInit();                         //UART��ʼ��(9600,8,NO,1)

    while (1)
    {
        if (1 == recv_finish)
        {
            recv_finish = 0;
            UART_SendByte(UART0, g_rxbuf);
        }
    }
}



