/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  UART模块例程
        上电发送 "Hello world!"后，等待串口接收，发送相同Byte
*备  注:  芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t i;
    uint8_t buf[] = {"Hello world!"};    //发送数据缓存

    SystemInit();
    DeviceClockAllEnable();

    EUARTInit();                         //UART初始化(9600,8,NO,1)

    for (i = 0; i < sizeof(buf); i++)
    {
        EUART_SendByte(buf[i]);

        while (EUART_GetFlagStatus(EUART_FLAG_TC) == RESET);

        EUART_ClearITPendingBit(EUART_CLR_TC);
    }

    while (1);                          //中断进行接收数据和发送
}



