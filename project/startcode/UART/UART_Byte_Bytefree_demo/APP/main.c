/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  UART模块例程
            自动检测空闲中断，当检测到空闲帧后，触发中断，接收Byte，发送相同Byte
*备  注:  芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t recv_finish = 0;

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    UARTInit();                         //UART初始化(9600,8,NO,1)

    while (1)
    {
        if (1 == recv_finish)
        {
            recv_finish = 0;
            UART_SendByte(UART0, g_rxbuf);
        }
    }
}



