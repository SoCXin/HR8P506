/*********************************************************
*Copyright (C), 2019, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  timer.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2019/11/29
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

    SCU_TIMEREN_Typedef t16n0_t16n1_en;
    t16n0_t16n1_en.Word = 0;

    dutyindex = 0;
    dutyNext = 0;

    /* 初始化T16Nx定时器*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //外部时钟PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWM模式
    x.T16Nx_PREMAT = 1;                         //不分频
    T16Nx_BaseInit(T16N0, &x);                  //初始化定时器T16N0
    T16Nx_BaseInit(T16N1, &x);                  //初始化定时器T16N1

    /*配置T16Nx通道输出*/
    z.T16Nx_MOE0 = Enable;                      //通道0输出开启
    z.T16Nx_MOE1 = Enable;                      //通道1输出开启
    z.T16Nx_POL0 = POSITIVE;                    //输出正极性
    z.T16Nx_POL1 = POSITIVE;                    //输出正极性
    z.T16Nx_PWMMODE = T16Nx_PWMMode_SYNC;       //同步模式输出
    z.PWMDZE = Disable;                         //关闭互补模式死区功能
    T16Nx_PMWOutInit(T16N0, &z);
    T16Nx_PMWOutInit(T16N1, &z);

    T16Nx_MAT0ITConfig(T16N0, T16Nx_Go_Int);     //CNT0匹配到MAT0继续计数
    T16Nx_MAT1ITConfig(T16N0, T16Nx_Go_Int);     //CNT0匹配到MAT1继续计数
    T16Nx_MAT2ITConfig(T16N0, T16Nx_Clr_Int);    //CNT0匹配到MAT2清零重新计数
    T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_High); //CNT0匹配到MAT0端口输出高
    T16Nx_MAT1Out0Config(T16N0, T16Nx_Out_Low);  //CNT0匹配到MAT1端口输出低
    T16Nx_SetCNT0(T16N0, 0);                     //设置T16N0初始值
    T16Nx_SetMAT0(T16N0, 800);                   //设置T16N0 MAT0值
    T16Nx_SetMAT1(T16N0, 1200);                  //设置T16N0 MAT1值
    T16Nx_SetMAT2(T16N0, 2000);                  //设置T16N0 MAT2值

    T16Nx_MAT0ITConfig(T16N1, T16Nx_Go_Int);     //CNT0匹配到MAT0继续计数
    T16Nx_MAT1ITConfig(T16N1, T16Nx_Go_Int);     //CNT0匹配到MAT1继续计数
    T16Nx_MAT2ITConfig(T16N1, T16Nx_Clr_Int);    //CNT0匹配到MAT2清零重新计数
    T16Nx_MAT0Out0Config(T16N1, T16Nx_Out_High); //CNT0匹配到MAT0端口输出高
    T16Nx_MAT1Out0Config(T16N1, T16Nx_Out_Low);  //CNT0匹配到MAT1端口输出低
    T16Nx_SetCNT0(T16N1, 0);                     //设置T16N1初始值
    T16Nx_SetMAT0(T16N1, 600);                   //设置T16N1 MAT0值
    T16Nx_SetMAT1(T16N1, 1400);                  //设置T16N1 MAT1值
    T16Nx_SetMAT2(T16N1, 2000);                  //设置T16N1 MAT2值

    T16Nx_ITConfig(T16N0, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N0_IRQn, NVIC_Priority_1, Enable);
    T16Nx_ITConfig(T16N1, T16Nx_IT_MAT0, Enable);
    NVIC_Init(NVIC_T16N1_IRQn, NVIC_Priority_1, Enable);
		
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func2;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A6, &y);                 //配置PA6为T16N0 输出通道0
    GPIO_Init(GPIO_Pin_A7, &y);                 //配置PA7为T16N0 输出通道1
    GPIO_Init(GPIO_Pin_A8, &y);                 //配置PA8为T16N1 输出通道0
    GPIO_Init(GPIO_Pin_A9, &y);                 //配置PA9为T16N1 输出通道1
		
    t16n0_t16n1_en.T16N0EN = Enable;
    t16n0_t16n1_en.T16N1EN = Enable;
    SCU_MultTimerEnable(t16n0_t16n1_en);         //SCU同步启动T16N0/T16N1

    return;
}

