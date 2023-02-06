/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/05
*描  述:  HR8P506主机从机通信demo。
          本程序为从机程序，负责接收数据和发送上一次接收的数据。
          使用ES-Bridge做主机，一次性发送255字节内的任意字节长度的unsigned char类型数据，然后再全部读取出来
          连线:
          PA4 - SCL
          PA5 - SDA
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t g_buf[255];

int main()
{
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();
    DeviceClockAllEnable();
    I2C0_SlaveInit();

    while (1)
    {

    }
}

