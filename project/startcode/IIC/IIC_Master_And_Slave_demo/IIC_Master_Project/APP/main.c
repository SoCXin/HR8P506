/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  506�����ӻ�ͨ��demo��������Ϊ�������򣬸�����д�Ͷ�����ӻ�д��һ�����ݺ��ٶ���������
          �����ӻ���Ҫ����SCL��PB2����SDA��PB3������������
*��  ע:   V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
    SystemInit();                   //����ʱ��
    DeviceClockAllEnable();         //����������ʱ��
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
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void I2C0_IRQHandler(void)
{


}




