/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  SPI主从机通信程序，本程序为从机程序，负责接收主机发来的数据，并保存起来。下次主机读的时候，发送保存的数据。
          引脚连接：PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO)
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
uint8_t spi_buf[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
uint8_t buf_count = 0;

int main()
{

    SystemInit();
    DeviceClockAllEnable();

    SPI1Init();

    while (1)
    {

    }
}
/***************************************************************
 函数名: void SPI1_IRQHandler(void)
 描  述：SPI中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void SPI1_IRQHandler(void)
{

    if (SPI_GetITStatus(SPI1, SPI_IT_NSS) == SET)
    {
        SPI_ClearITPendingBit(SPI1, SPI_CLR_NSS);
        Clear_RBR(SPI1);
        Clear_TBW(SPI1);
        buf_count = 0;

        if (SPI_GetStatus(SPI1, SPI_STA_NSS) == SET)     //片选未选中
        {
            SPI_ITConfig(SPI1, SPI_IT_TB, Disable);
        }
        else
        {
            SPI_ITConfig(SPI1, SPI_IT_RB, Enable);
            SPI_RBIMConfig(SPI1, SPI_IType_BYTE);
        }
    }

    if (SPI_GetITStatus(SPI1, SPI_IT_RB) == SET)
    {
        spi_buf[buf_count] = SPI_RecByte(SPI1);
        buf_count ++;

        if (buf_count == 1)
        {
            if (spi_buf[0] == (Slave_Addr | 0x01))      //主机读
            {
                SPI_SendByte(SPI1, spi_buf[buf_count]);
                buf_count ++;

                SPI_ITConfig(SPI1, SPI_IT_TB, Enable);
                SPI_ITConfig(SPI1, SPI_IT_RB, Disable);
                SPI_TBIMConfig(SPI1, SPI_IType_BYTE);
            }
            else if (spi_buf[0] == Slave_Addr)
            {
                Clear_TBW(SPI1);
                SPI_ITConfig(SPI1, SPI_IT_TB, Disable);
            }
        }
    }

    if (SPI_GetITStatus(SPI1, SPI_IT_TB) == SET)
    {
        SPI_SendByte(SPI1, spi_buf[buf_count]);
        buf_count ++;
    }
}
