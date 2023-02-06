/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  UART模块例程
          使用UART0的PA23发送，使用38KPWM调制，红外收发，发送数据0x55,接收判断后，将接收的0x55发送，点灯指示
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#include "systick.h"

extern uint8_t g_rxbuf;

int main(void)
{
    SystemInit();                //配置时钟
    DeviceClockAllEnable();      //打开所有外设时钟

    User_SysTickInit();
    LightInit();
    UARTInit();                         //UART初始化(1200,8,NO,1)

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



