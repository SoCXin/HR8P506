/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/11
*描  述:  IIC模块例程
		  本程序为主机程序，负责发起写和读。从从机中读取9字节数据后，然后发给从机。。
          连线：
		  PA4 - SCL
		  PA5 - SDA
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "main.h"

uint8_t rxbuf[9];
uint8_t txbuf[9];
	
int main()
{
	PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();                   			/* 配置时钟 */
    DeviceClockAllEnable();         			/* 打开所有外设时钟 */
	User_SysTickInit();
	
    IICMasterInitPins();
	
    while (1)
    {
		IICReadBuf(SLAVE_ADDR, rxbuf, 9);
		memcpy(txbuf, rxbuf, 9);
		Delay_10us(200000);
        IICWriteBuf(SLAVE_ADDR, txbuf, 9);
        Delay_10us(200000);
	}
}

