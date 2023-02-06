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
函数名: void T16N3Init(void)
描  述: T16N3定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T32NxInit(void)
{
    T32Nx_BaseInitStruType x;

    /* 初始化T16Nx定时器*/
    x.T32Nx_ClkS = T32Nx_ClkS_PCLK;             //外部时钟CK0
    x.T32Nx_SYNC = Disable;
    x.T32Nx_EDGE = T32Nx_EDGE_Rise;
    x.T32Nx_Mode = T32Nx_Mode_TC0;              //定时器计数器模式
    x.T32Nx_PREMAT = 1;
    T32Nx_BaseInit(T32N0, &x);                  //初始化定时器T32N0

    /* 设置定时器 */
    T32Nx_MAT0ITConfig(T32N0, T32Nx_Clr_Int);   //MAT0匹配设置
    T32Nx_SetCNT(T32N0, 0);                     //设置T32N0初始值为0
    T32Nx_SetMAT0(T32N0, 400000);               //设置T32N0MAT0值为40000
    T32Nx_ITConfig(T32N0, T32Nx_IT_MAT0, Enable); //使能T32N0匹配0中断
    NVIC_Init(NVIC_T32N0_IRQn, NVIC_Priority_1, Enable); //中断设置
    T32Nx_Enable(T32N0);

    return;
}

