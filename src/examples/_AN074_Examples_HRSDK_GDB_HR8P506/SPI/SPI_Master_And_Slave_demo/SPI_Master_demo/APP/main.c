/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/14
*描  述:  主机从机通信demo，本程序为主机程序，负责发起写和读。MCU读取10字节数据，再发回10字节数据。
          默认使用中断的方式接收数据。空闲时的时钟信号是低电平,第二边沿采样
          引脚连接：
          PA2-NSS,
          PA3-SCK,
          PA4-MISO,
          PA5-MOSI
          修改spi.c中的宏定义，当ISR定义为1时，MCU采用中断方式进行数据的收发，
          当ISR定义为0时，MCU采用查询方式进行收发，使用查询方式须适当降低波特率。
          本例程使用ES-Bridge进行测试，ES-Bridge作为从机来测试SPI的收发。
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"


int main()
{
    uint8_t w_buf[12] = {0x0};
    uint8_t r_buf[12] = {0x0};

    
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();
    DeviceClockAllEnable();
    User_SysTickInit();

    SPI1Init();

    while (1)
    {
        SPIReadData(r_buf, 10);
        Delay_1ms(3000);
        memcpy(w_buf, r_buf, 10);
        SPIWriteData(w_buf, 10);
        Delay_1ms(3000);
    }
}

