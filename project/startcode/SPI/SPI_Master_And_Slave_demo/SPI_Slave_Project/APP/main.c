/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  SPI���ӻ�ͨ�ų��򣬱�����Ϊ�ӻ����򣬸�������������������ݣ��������������´���������ʱ�򣬷��ͱ�������ݡ�
          �������ӣ�PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO)
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
 ������: void SPI1_IRQHandler(void)
 ��  ����SPI�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void SPI1_IRQHandler(void)
{

    if (SPI_GetITStatus(SPI1, SPI_IT_NSS) == SET)
    {
        SPI_ClearITPendingBit(SPI1, SPI_CLR_NSS);
        Clear_RBR(SPI1);
        Clear_TBW(SPI1);
        buf_count = 0;

        if (SPI_GetStatus(SPI1, SPI_STA_NSS) == SET)     //Ƭѡδѡ��
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
            if (spi_buf[0] == (Slave_Addr | 0x01))      //������
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
