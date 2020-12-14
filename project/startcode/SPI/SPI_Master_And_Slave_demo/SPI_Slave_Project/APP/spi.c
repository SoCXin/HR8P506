/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  SPI�ӻ�ģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "spi.h"

/*********************************************************
������: void SPIInit(void)
��  ��: SPI�ӻ���ʼ���ӳ���
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
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;


    GPIO_Init(GPIO_Pin_A25, &x);                //DI  - PA25
    GPIO_Init(GPIO_Pin_A26, &x);                //CLK - PA26
    GPIO_Init(GPIO_Pin_A27, &x);                //CS  - PA27

    x.Dir = GPIO_Direction_Output;
    GPIO_Init(GPIO_Pin_A24, &x);                //DO  - PA24

    y.SPI_Freq = 10000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Slave;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                   //��ʱ������
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         //���սṹ��Ĳ�������SPI

    SPI_ITConfig(SPI1, SPI_IT_NSS, Enable);
    NVIC_Init(NVIC_SPI1_IRQn, NVIC_Priority_0, Enable);

    SPI1_RecEnable();
    SPI1_Enable();                              //ʹ��SPI
}

