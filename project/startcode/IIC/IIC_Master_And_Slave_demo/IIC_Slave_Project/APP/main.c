/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  506�����ӻ�ͨ��demo��������Ϊ�ӻ����򣬸���������ݺͷ�����һ�ν��յ����ݡ�
        �����ӻ���Ҫ����SCL��PB2����SDA��PB3������������
*��  ע:   V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/

#include "iic.h"
#include "system_HR8P506.h"



int main()
{
    SystemInit();                   //����ʱ��
    DeviceClockAllEnable();         //����������ʱ��
    I2C0_SlaveInit();

    while (1)
    {

    }

}

/***************************************************************
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
                 �û���Ҫ���ٴ���ʱ������ʹ�ò����Ĵ����ķ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
unsigned char iic_buf[8];
unsigned char buf_count = 0;
void I2C0_IRQHandler(void)
{
    if (IIC_GetITStatus(I2C0, IIC_IT_SR) == SET) //�յ���ʼλ+��ַƥ��+����Ӧ��λ
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);            //��I2C��ʼλ+��ַƥ��+����Ӧ��λ��־λ

        if (IIC_GetRWMode(I2C0) == IIC_Mode_Read) //������
        {
            IIC_ITConfig(I2C0, IIC_IT_RB, Disable);

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_TIDLE, Enable);
            buf_count = 0;

            IIC_SendByte(I2C0, iic_buf[buf_count++]);       //д���ͻ����������ֽ�
        }
        else if (IIC_GetRWMode(I2C0) == IIC_Mode_Write) //����д
        {
            IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
            IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
            buf_count = 0;
        }
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_RB) == SET) //I2C���ջ������н�������
    {
        iic_buf[buf_count++] = IIC_RecByte(I2C0); //�����ջ�������Ӳ��������жϱ�־
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_TIDLE) == SET) //I2C����
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);

        if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) != SET) //û�н��յ�NACK
        {
            IIC_SendByte(I2C0, iic_buf[buf_count++]);       //д���ͻ�����
        }
    }

    if (IIC_GetITStatus(I2C0, IIC_IT_SP) == SET) //�յ�����λ
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);            //�����λ�жϱ�־
        IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
        IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
        IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
        buf_count = 0;
    }
}




