/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  light.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/25
*描  述:  LIGHT指示灯模块程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "light.h"

/***************************************************************
 函数名：void LightInit(void)
 描  述：LIGHT指示灯闪烁初始化
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void LightInit(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A6, &x);
    GPIO_Init(GPIO_Pin_A7, &x);
    GPIO_Init(GPIO_Pin_A8, &x);
    GPIO_Init(GPIO_Pin_A9, &x);

    return;
}
