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
函数名: void T16NxInit(void)
描  述: T16Nx定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16NxInit(void)
{
    T16Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T16Nx_PWMInitStruType z;

    dutyindex = 0;
    dutyNext = 0;

    /* 初始化T16Nx定时器*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //外部时钟PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWM模式
    x.T16Nx_PREMAT = 80;                        //预分频比为1:80
    T16Nx_BaseInit(T16N0, &x);                  //初始化定时器T16N0
    T16Nx_BaseInit(T16N3, &x);                  //初始化定时器T16N3

    /*配置T16N0通道0输出*/
    z.T16Nx_MOE0 = Enable;                      //通道0输出开启
    z.T16Nx_MOE1 = Enable;                      //通道1输出开启
    z.T16Nx_POL0 = POSITIVE;                    //输出正极性
    z.T16Nx_POL1 = POSITIVE;                    //输出正极性
    z.T16Nx_PWMMODE = T16Nx_PWMMode_INDEP;      //独立模式输出
    z.PWMDZE = Disable;                         //关闭互补模式死区功能
    T16Nx_PMWOutInit(T16N0, &z);

    T16Nx_MAT0ITConfig(T16N0, T16Nx_Clr_Int);   //CNT0匹配到MAT0清零重新计数
    T16Nx_MAT1ITConfig(T16N0, T16Nx_Go_No);     //CNT0匹配到MAT1继续计数
    T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_High); //CNT0匹配到MAT0端口输出高
    T16Nx_MAT1Out0Config(T16N0, T16Nx_Out_Low); //CNT0匹配到MAT1端口输出低
    T16Nx_SetCNT0(T16N0, 0);                    //设置T16N0初始值为0
    T16Nx_SetMAT0(T16N0, Period);               //设置T16N0MAT0值为周期
    T16Nx_SetMAT1(T16N0, dutytab[0]);           //设置T16N0MAT1值为占空比

    /*配置T16N0 通道1输出*/
    T16Nx_MAT2ITConfig(T16N0, T16Nx_Clr_Int);   //CNT1匹配到MAT2清零重新计数
    T16Nx_MAT3ITConfig(T16N0, T16Nx_Go_No);     //CNT1匹配到MAT3继续计数
    T16Nx_MAT2Out1Config(T16N0, T16Nx_Out_High); //CNT10匹配到MAT0端口输出高
    T16Nx_MAT3Out1Config(T16N0, T16Nx_Out_Low); //CNT1匹配到MAT1端口输出低
    T16Nx_SetCNT1(T16N0, 0);                    //设置T16N0初始值为0
    T16Nx_SetMAT2(T16N0, Period);               //设置T16N0MAT2值为周期
    T16Nx_SetMAT3(T16N0, (Period / 2));         //设置T16N0MAT3值为占空比

    T16Nx_ITConfig(T16N0, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N0_IRQn, NVIC_Priority_1, Enable);

    /*配置T16N3通道1输出*/
    z.T16Nx_MOE0 = Disable;                     //通道0输出关闭
    z.T16Nx_MOE1 = Enable;                      //通道1输出开启
    z.T16Nx_POL0 = POSITIVE;                    //输出正极性
    z.T16Nx_POL1 = POSITIVE;                    //输出正极性
    z.T16Nx_PWMMODE = T16Nx_PWMMode_INDEP;      //独立模式输出
    z.PWMDZE = Disable;                         //关闭互补模式死区功能
    T16Nx_PMWOutInit(T16N3, &z);

    T16Nx_MAT2ITConfig(T16N3, T16Nx_Clr_Int);   //CNT1匹配到MAT2清零重新计数
    T16Nx_MAT3ITConfig(T16N3, T16Nx_Go_No);     //CNT1匹配到MAT3继续计数
    T16Nx_MAT2Out1Config(T16N3, T16Nx_Out_High); //CNT1匹配到MAT2端口输出高
    T16Nx_MAT3Out1Config(T16N3, T16Nx_Out_Low); //CNT1匹配到MAT3端口输出低
    T16Nx_SetCNT1(T16N3, 0);                    //设置T16N3初始值为0
    T16Nx_SetMAT2(T16N3, Period);               //设置T16N3MAT2值为周期
    T16Nx_SetMAT3(T16N3, Period / 2);           //设置T16N3MAT3值为占空比
		
    /* 初始化PWM输出口*/
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func3;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B1, &y);                 //配置PB1为T16N3 输出通道1

    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func2;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A6, &y);                 //配置PA6为T16N0 输出通道0
    GPIO_Init(GPIO_Pin_A7, &y);                 //配置PA7为T16N0 输出通道1
		
    T16Nx_Enable(T16N0);                        //使能T16N0
    T16Nx_Enable(T16N3);                        //使能T16N3

    return;
}

