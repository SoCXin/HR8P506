/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/09
*描  述:  主机从机通信demo，本程序为从机程序，上位机使用ES-Bridge。
          引脚连接：
          PA2-NSS,
          PA3-SCK,
          PA4-MISO,
          PA5-MOSI
          MCU接收主机发送过来的数据（最长8字节），并保存起来，下次主机读的时候，发送保存的数据
          需要注意的是，通信波特率不得超过656K
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
uint8_t g_wbuf[8];
uint8_t g_rbuf[8];

int main()
{
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();
    DeviceClockAllEnable();

    SPI1Init();

    while (1);
}
