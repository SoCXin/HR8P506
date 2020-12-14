/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  adc.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  ADC模块程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "adc.h"

/***************************************************************
 函数名：ADCInit
 描  述：ADC 初始化
 输入值：无
 输出值：无
 返回值：无
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
    x.CLKDIV = ADC_CLKDIV_1_32;     //ADC转换时钟源一定要符合数据手册中ADC转化时钟源选择表
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
函数名: ADCRead
描  述: ADC采样数据读取(16次采样平均值)(硬件控制)
输入值: 无
输出值: 无
返回值: 平均值
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
