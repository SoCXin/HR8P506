/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  506主机从机通信demo，本程序为主机程序，负责发起写和读。向从机写入一个数据后，再读回主机。
          引脚连接：PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO)
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t wbuf[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint8_t rbuf[8] ;

void delay(void)
{
    int i, j;

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {;}
    }
}

int main()
{
    uint8_t i = 0;
    SystemInit();
    DeviceClockAllEnable();

    SPI1Init();

    while (1)
    {
        for (i = 0; i < 8; i ++)
        {
            wbuf[i] ++;
        }

        SPIWriteData(wbuf, 8);
        delay();
        SPIReadData(rbuf, 8);
        delay();
    }
}
