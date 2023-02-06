/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/11
*描  述:  IIC E2PROM demo
          引脚连接：
          ------------------------
          IIC EEPROM:
          ------------------------
          PB2 - SCL
          PB3 - SDA
          ------------------------
          UART:
          ------------------------
          TXD - PA23
          RXD - PA22
          ------------------------
          本例程使用的E2PROM型号为24C04B(4K)，可直接连接通用开发板HRSDK-GMB-01
          上位机使用XCOM接收MCU发送的数据
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "main.h"
#include "iic.h"

uint8_t wbuf[20];
uint8_t rbuf[20] ;

int main()
{
    PLLClock_Config(Enable, SCU_PLL_IN16M, SCU_PLL_48M, Enable);	/* PLL使能，倍频到48M */
	SystemCoreClock = 48000000;
    SystemInit();                               /* 配置时钟 */
    DeviceClockAllEnable();                     /* 打开所有外设时钟 */

    User_SysTickInit();
    e2prom_init();

    /* 在E2PROM的0x13地址上写入0xCD */
    e2prom_byte_write(0x13, 0xCD, rom_size_1k);
    printf("write finished, write content: 0xCD in hex, 205 in decimal\n\r");

    /* 从E2PROM的0x13地址上读取一字节数据 */
    e2prom_random_read(0x13, rbuf, rom_size_1k);
    printf("content readout: %d\n\r\n\r", rbuf[0]);

    /* 在E2PROM的0xA0地址处写入essemi */
    memcpy(wbuf, "essemi", 6);
    e2prom_page_write(0xA0, wbuf, page_size_8, rom_size_1k);
    printf("write finished, write content: essemi\n\r");

    /* 从E2PROM的0xA0地址处读取6字节数据 */
    e2prom_sequential_read(0xA0,rbuf, 6, rom_size_1k);
    printf("content readout: %s\n\r\n\r", rbuf);

    while (1)
    {
    }

}

