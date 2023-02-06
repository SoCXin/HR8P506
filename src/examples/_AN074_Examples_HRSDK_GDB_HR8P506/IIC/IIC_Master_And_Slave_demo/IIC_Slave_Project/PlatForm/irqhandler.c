#include "irqhandler.h"


/***************************************************************
***************************************************************/
uint8_t rxcnt;
uint8_t txcnt;


/***************************************************************
***************************************************************/
void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1)
    {
    }
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{

}


/***************************************************************
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
         �û���Ҫ���ٴ���ʱ������ʹ�ò����Ĵ����ķ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void I2C0_IRQHandler(void)
{
    /* �յ���ʼλ+��ַƥ��+����Ӧ��λ */
    if (IIC_GetITStatus(I2C0, IIC_IT_SR) == SET)
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

        if (IIC_GetRWMode(I2C0) == IIC_Mode_Read)
        {
            txcnt = 0x0U;

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
            IIC_ITConfig(I2C0, IIC_IT_TB, Enable);
        }
        else if (IIC_GetRWMode(I2C0) == IIC_Mode_Write)
        {
            rxcnt = 0x0U;

            IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
            IIC_ClearITPendingBit(I2C0, IIC_CLR_TIDLE);
            IIC_ITConfig(I2C0, IIC_IT_RB, Enable);
            IIC_ITConfig(I2C0, IIC_IT_TB, Disable);
        }
    }

    /* �����ж� */
    if (IIC_GetITStatus(I2C0, IIC_IT_RB) == SET)
    {
        g_buf[rxcnt++] = IIC_RecByte(I2C0);
    }

    /* �����ж� */
    if (IIC_GetITStatus(I2C0, IIC_IT_TB) == SET)
    {
        if (IIC_GetFlagStatus(I2C0, IIC_IF_NA) != SET)
        {
            IIC_SendByte(I2C0, g_buf[txcnt++]);
        }
    }

    /* �յ�����λ */
    if (IIC_GetITStatus(I2C0, IIC_IT_SP) == SET) 
    {
        IIC_ClearITPendingBit(I2C0, IIC_CLR_SP);
        IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);

        IIC_ITConfig(I2C0, IIC_IT_RB, Disable);
        IIC_ITConfig(I2C0, IIC_IT_TIDLE, Disable);
    }
}
