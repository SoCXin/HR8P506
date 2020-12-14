/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  UART模块例程
        上电后自动检测波特率执行一次，按照第一次通信成功波特率通信，等待串口接收，发送相同Byte
*备  注:  芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    UARTInit();                         //UART初始化(9600,8,NO,1)

    while (1);                          //中断进行接收数据和发送
}



