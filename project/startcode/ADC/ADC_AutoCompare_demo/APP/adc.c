/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  adc.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/28
*��  ��:  ADCģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "adc.h"

/***************************************************************
��������ADCInit
��  ����ADC ��ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void ADCInit(void)
{
    ADC_InitStruType x;
    GPIO_InitSettingType y;

    y.Signal = GPIO_Pin_Signal_Analog;
    y.Dir = GPIO_Direction_Input;
    y.Func = GPIO_Reuse_Func0;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B6, &y);

    x.CLKS = ADC_CLKS_PCLK;
    x.CLKDIV = ADC_CLKDIV_1_32;     //ADCת��ʱ��Դһ��Ҫ���������ֲ���ADCת��ʱ��Դѡ���
    x.VREF_SEL = ADC_VREF_SEL_1_8;
    x.VREFP = ADC_VREFP_IO;
    x.VREFN = ADC_VREFN_VSS;
    x.CHS = ADC_CHS_AIN1;
    x.SMPS = ADC_SMPS_HARD;
    x.ST = 8;
    ADC_Init(&x);

    ADC_IE_Enable();
    NVIC_Init(NVIC_ADC_IRQn, NVIC_Priority_1, Enable);
}

/***************************************************************
 ��������ADCACPConfig
 ��  ����ADC ACP���ܳ�ʼ��
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void ADCACPConfig(void)
{
    ADC_ACP_TypeDef x;

    x.ACP_EN = ENABLE;
    x.ACPC_OVER_TIME = 0X3F;
    x.ACPC_TIMES = ADC_ACPC_TIMES_8;
    x.ACPC_MIN_TARGET = 0XFFF;
    x.ACPC_MAX_TARGET = 0x100;                          /* ��meanֵ���ڸ�ֵʱ���ᴥ���ж� */
    ADC_ACPConfig(&x);


}
