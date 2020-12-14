/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  adc.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
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

    NVIC_Init(NVIC_ADC_IRQn, NVIC_Priority_1, Enable);
    ADC_IE_Enable();
}

/*********************************************************
������: ADCRead
��  ��: ADC�������ݶ�ȡ(16�β���ƽ��ֵ)(Ӳ������)
����ֵ: ��
���ֵ: ��
����ֵ: ƽ��ֵ
**********************************************************/
uint16_t ADCRead(void)
{
    uint8_t i;
    uint32_t max, min, sum, ad_temp;

    max = 0x00;
    min = 0x0FFF;
    sum = 0x00;

    for (i = 0; i < 18; i++)
    {
        ADC_Start();

        while (ADC_GetIFStatus(ADC_IF) == RESET);

        ad_temp = ADC_GetConvValue();
        ADC_ClearIFStatus(ADC_IF);

        if (ad_temp > max)
        {
            max = ad_temp;
        }

        if (ad_temp < min)
        {
            min = ad_temp;
        }

        sum += ad_temp;
    }

    sum -= min;
    sum -= max;

    return sum >> 4;
}
