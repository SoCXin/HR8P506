/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  adc.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
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

    ADC_IE_Enable();
    NVIC_Init(NVIC_ADC_IRQn, NVIC_Priority_1, Enable);
}

/***************************************************************
 函数名：ADCACPConfig
 描  述：ADC ACP功能初始化
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void ADCACPConfig(void)
{
    ADC_ACP_TypeDef x;

    x.ACP_EN = ENABLE;
    x.ACPC_OVER_TIME = 0X3F;
    x.ACPC_TIMES = ADC_ACPC_TIMES_8;
    x.ACPC_MIN_TARGET = 0XFFF;
    x.ACPC_MAX_TARGET = 0x100;                          /* 当mean值大于该值时，会触发中断 */
    ADC_ACPConfig(&x);


}
