/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  506主机从机通信demo，本程序为主机程序，负责发起写和读。向从机写入一个数据后，再读回主机。
          主机从机需要连接SCL（PB2）和SDA（PB3），并上拉。
*备  注:   V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "iic.h"
#include "system_HR8P506.h"

void delay(void)
{
    int i, j;

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {;}
    }
}


char wbuf[8] = {1, 2, 3, 4, 5, 6, 7, 8};
char rbuf[8] ;
int main()
{

    char i = 0;
    SystemInit();                   //配置时钟
    DeviceClockAllEnable();         //打开所有外设时钟
    IICMasterInit();

    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            wbuf[i]++;
        }

        IICWriteBuf(SLAVE_ADDR, wbuf, 8);
        delay();
        IICReadBuf(SLAVE_ADDR, rbuf, 8);
        delay();
    }

}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{


}




