/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  SPI����ģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "spi.h"

/*********************************************************
������: void SPIInit(void)
��  ��: SPI������ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void SPI1Init(void)
{
    GPIO_InitSettingType x;
    SPI_InitStruType y;

    /* PA 24 25 26 27 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A24, &x);                //DO  - PA24
    GPIO_Init(GPIO_Pin_A25, &x);                //DI  - PA25
    GPIO_Init(GPIO_Pin_A26, &x);                //CLK - PA26

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A27, &x);                //CS  - PA27

    y.SPI_Freq = 10000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                   //��ʱ������
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         //���սṹ��Ĳ�������SPI

    SPI1_RecEnable();
    SPI1_Enable();                              //ʹ��SPI
}
/*********************************************************
������: SPIReadData(uint8_t *rbuf, uint8_t n)
��  ��: SPI�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: n���������ݸ���
���ֵ: rbuf���������ݻ���
����ֵ: ��
**********************************************************/
void SPIReadData(uint8_t *rbuf, uint8_t n)
{
    uint8_t i;

    GPIO_ResetBit(GPIO_Pin_A27);                                           //cs

    for (i = 0; i < 10; i ++);

    SPI_SendByte(SPI1, Slave_Addr | 0x01);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    for (i = 0; i < 50; i ++);

    Clear_RBR(SPI1);

    for (i = 0; i < n; i++)                             //����
    {
        while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        SPI_SendByte(SPI1, 0);

        while (SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == RESET);

        rbuf[i] = SPI_RecByte(SPI1);
    }

    for (i = 0; i < 10; i ++);

    GPIO_SetBit(GPIO_Pin_A27);                                         //cs
}

/*********************************************************
������: SPIWriteData(uint8_t *wbuf, uint8_t n)
��  ��: SPIд���ݣ������ֽڶ���
����ֵ: wbuf-�������ݻ���
        n���������ݸ���
���ֵ: ��
����ֵ: ��
**********************************************************/
void SPIWriteData(uint8_t *wbuf, uint8_t n)
{
    uint16_t i;

    GPIO_ResetBit(GPIO_Pin_A27);

    for (i = 0; i < 10; i ++);

    SPI_SendByte(SPI1, Slave_Addr);

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    for (i = 0; i < 10; i ++);

    for (i = 0; i < n; i++)
    {
        SPI_SendByte(SPI1, wbuf[i]);

        while (SPI_GetFlagStatus(SPI1, SPI_Flag_TB) == RESET);
    }

    while (SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    for (i = 0; i < 10; i ++);

    GPIO_SetBit(GPIO_Pin_A27);
}
