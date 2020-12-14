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

unsigned int Period = 1000;
unsigned int dutytab[6] = {0, 200, 400, 600, 800, 1000};
unsigned int dutyindex;
unsigned int dutyNext;

/*********************************************************
函数名: void T32NxInit(void)
描  述: T32Nx定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32NxInit(void)
{
    T32Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T32Nx_PWMInitStruType z;

    dutyindex = 0;
    dutyNext = 0;

    /* 初始化PWM输出口  */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func1;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B1, &y);                     //配置PB1为T32N0 输出通道1

    /* 初始化T32Nx定时器*/
    x.T32Nx_ClkS = T32Nx_ClkS_PCLK;                 //内部PCLK
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Rise;
    x.T32Nx_Mode = T32Nx_Mode_PWM;                  //定时器计数器模式
    x.T32Nx_PREMAT = 20;                            //预分频比为1:20
    T32Nx_BaseInit(T32N0, &x);                      //初始化定时器T32N0

    /*初始化T32N0PWM输出*/
    z.T32Nx_MOE0 = Disable;
    z.T32Nx_MOE1 = Enable;                          //使能通道1输出
    T32Nx_PMWOutInit(T32N0, &z);                    //初始化T32N0为PWM模式

    T32Nx_MAT2ITConfig(T32N0, T32Nx_Clr_Int);       //CNT0匹配到MAT2清零重新计数
    T32Nx_MAT3ITConfig(T32N0, T32Nx_Go_Int);        //CNT0匹配到MAT3继续计数
    T32Nx_MAT2Out1Config(T32N0, T32Nx_Out_High);    //CNT0匹配到MAT3端口输出低
    T32Nx_MAT3Out1Config(T32N0, T32Nx_Out_Low);     //CNT0匹配到MAT3端口输出低
    T32Nx_SetCNT(T32N0, 0);                         //设置T32N0初始值为0
    T32Nx_SetMAT2(T32N0, Period);                   //设置T32N0MAT2值为周期
    T32Nx_SetMAT3(T32N0, dutytab[1]);               //设置T32N0MAT3值为占空比

    T32Nx_ITConfig(T32N0, T32Nx_IT_MAT2, Enable);
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable);
    T32Nx_Enable(T32N0);                            //使能T32N0定时器

    return;
}

