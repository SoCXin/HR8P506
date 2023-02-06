/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/14
*描  述:  SPI EEPROM demo
          引脚连接：
          ------------------------
          SPI EEPROM:
          ------------------------
          NSS - PA27,
          SCK - PA26,
          MISO - PA25,
          MOSI - PA24
          ------------------------
          UART:
          ------------------------
          TXD - PA23
          RXD - PA22
          ------------------------
          本例程使用的外部FLASH型号为93AA46A，可直接连接通用开发板HRSDK-GMB-01
          上位机使用XCOM接收MCU发送的数据
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint8_t w_buffer[1] = {0xCD};
    uint8_t r_buffer[1] = {0x0};

    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();
    DeviceClockAllEnable();
    User_SysTickInit();

    E2rom_init();

    E2romEraseAll();
    E2romWriteData(0x00, w_buffer[0]);
    printf("E2ROM writeten finished, content: %d\n\r", w_buffer[0]);

    E2romReadData(0x00, r_buffer);
    printf("Content readout from E2ROM: %d\n\r\n\r", r_buffer[0]);

    while (1)
    {
    }
}

