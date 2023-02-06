/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  gpio.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/13
*描  述:  外部端口中断配置程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "gpio.h"
#include "string.h"
/***************************************************************
 函数名：void GPIO_Init(void)
 描  述：端口中断初始化函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void GPIOInit(void)
{
    GPIO->PAINEB.Word = 0XFFFFFFFF; //输入关闭
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //输出打开
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00000040;  //PA6输出高关闭LED1
    GPIO->PBDATA.Word = 0X00000080;  //PB7有上拉电阻
}
/***************************************************************
 函数名：void PINTx_Init(void)
 描  述：端口中断初始化函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void PINTx_Init(void)
{
    GPIO_InitSettingType x;
    PINT_InitSettingType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A1, &x);

    y.IE_Set = PINT_IE_Set_Enable;
    y.Trigger_Style = PINT_Trigger_Rising_Edge;
    PINT_Init(GPIO_Pin_A1, &y);
    NVIC_Init(NVIC_PINT1_IRQn, NVIC_Priority_1, Enable);

    return;
}

/***************************************************************
 函数名：void KINTx_Init(void)
 描  述：按键中断初始化函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void KINTx_Init(void)
{
    GPIO_InitSettingType x;
    KINT_InitSettingType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A3, &x);

    y.IE_Set = KINT_IE_Set_Enable;
    y.Trigger_Style = KINT_Trigger_Rising_Edge;
    KINT_Init(GPIO_Pin_A3, &y);
    NVIC_Init(NVIC_KINT_IRQn, NVIC_Priority_1, Enable);

    return;
}
