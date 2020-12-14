/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  timer.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  Timer模块程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "timer.h"

/*********************************************************
函数名: void T32N0CAP_Init(void)
描  述: T32N0初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32N0CAP_Init(void)
{
    T32Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T32Nx_CapInitStruType z;

    /* 初始化T32N0定时器*/
    x.T32Nx_ClkS = T32Nx_ClkS_PCLK;
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Rise;
    x.T32Nx_Mode = T32Nx_Mode_CAP;
    x.T32Nx_PREMAT = 1;
    T32Nx_BaseInit(T32N0, &x); //初始化定时器T32N0

    /*输入捕捉引脚PB0初始化*/
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Input;
    y.Func = GPIO_Reuse_Func1;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &y);

    /*初始化T32N0捕捉功能*/
    z.T32Nx_CAPCAPL1 = Disable;
    z.T32Nx_CAPCAPL0 = Enable;
    z.T32Nx_CapRise = Enable;
    z.T32Nx_CapFall = Disable;
    z.T32Nx_CapIS0 = Enable;
    z.T32Nx_CapIS1 = Disable;
    z.T32Nx_CapTime = T32Nx_CapTime_2;                  //捕捉2次
    T32Nx_CapInit(T32N0, &z);

    T32Nx_MAT0ITConfig(T32N0, T32Nx_Go_No);             //MAT0匹配设置
    T32Nx_MAT2ITConfig(T32N0, T32Nx_Go_No);             //MAT2匹配设置
    T32Nx_ITConfig(T32N0, T32Nx_IT_CAP0, Enable);       //使能T32N0输入捕捉0中断
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable); //中断设置
    T32Nx_Enable(T32N0);

    return;
}

/*********************************************************
函数名: void T16N3Init(void)
描  述: T16N3定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N2Init(void)
{
    T16Nx_BaseInitStruType x;

    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;                     //内部时钟PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //定时器计数器模式
    x.T16Nx_PREMAT = 4;
    T16Nx_BaseInit(T16N2, &x);                          //初始化定时器T16N3

    T16Nx_MAT0ITConfig(T16N2, T16Nx_Clr_Int);           //MAT0匹配设置
    T16Nx_SetCNT0(T16N2, 0);                            //设置T16N2初始值为0
    T16Nx_SetMAT0(T16N2, SystemCoreClock / 1000);       //设置T16N2MAT0值
    T16Nx_ITConfig(T16N2, T16Nx_IT_MAT0, Enable);       //使能T16N2匹配0中断
    NVIC_Init(NVIC_T16N2_IRQn, NVIC_Priority_1, Enable); //中断设置
    T16Nx_Enable(T16N2);

    return;
}

