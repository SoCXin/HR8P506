/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  light.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/13
*描  述:  LIGHT指示灯模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "light.h"

/***************************************************************
 函数名：void LightInit(void)
 描  述：LIGHT指示灯闪烁初始化
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void LightInit(GPIO_Pin Pin)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    if (Pin == LED1_PIN)
        GPIO_Init(LED1_PIN, &x);
    else if (Pin == LED2_PIN)
        GPIO_Init(LED2_PIN, &x);
    else if (Pin == LED3_PIN)
        GPIO_Init(LED3_PIN, &x);
    else if (Pin == LED4_PIN)
        GPIO_Init(LED4_PIN, &x);

    return;
}


/***************************************************************
 函数名：void LightOn(void)
 描  述：LIGHT指示灯常亮
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void LightOn(GPIO_Pin Pin)
{
    if (Pin == LED1_PIN)
        GPIO_WriteBit(LED1_PIN, 0);
    else if (Pin == LED2_PIN)
        GPIO_WriteBit(LED2_PIN, 0);
    else if (Pin == LED3_PIN)
        GPIO_WriteBit(LED3_PIN, 0);
    else if (Pin == LED4_PIN)
        GPIO_WriteBit(LED4_PIN, 0);

    return;
}

/***************************************************************
 函数名：void LightOff(void)
 描  述：LIGHT指示灯熄灭
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void LightOff(GPIO_Pin Pin)
{
    if (Pin == LED1_PIN)
        GPIO_WriteBit(LED1_PIN, 1);
    else if (Pin == LED2_PIN)
        GPIO_WriteBit(LED2_PIN, 1);
    else if (Pin == LED3_PIN)
        GPIO_WriteBit(LED3_PIN, 1);
    else if (Pin == LED4_PIN)
        GPIO_WriteBit(LED4_PIN, 1);

    return;
}
