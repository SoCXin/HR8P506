/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:
*版  本:  V1.01
*日  期:  2018/03/26
*描  述:  sleep示例程序，单独使用子板进行试验(需要断开子板上电源指示灯的限流电阻)，
          当供电电压低于3.6V进行休眠程序
          当供电电压高于4v退出休眠程序，PA23连续翻转
          休眠程序唤醒源如下：
          1.WDT唤醒后清狗
          2.按键唤醒(PA22接0)后PA23连续翻转7次
          3.LVD唤醒系统软复位退出休眠函数
          注意：当进行LVD唤醒试验并使用电流表测量电流时，电流表请设置在毫安档(微安档内阻过大影响供电电压)
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t g_sleep_flag = 0;
int main(void)
{
    uint32_t i;
    GPIO_InitSettingType x;//声明一个结构体名x
    SystemInit();          //系统初始化
    DeviceClockAllEnable(); //打开所有外设时钟

    //for(i=0; i<1055350; i++);
    //以下开始检测LVD电压是否满足进入低功耗状态
    SCU_RegUnLock(); //scu写保护解锁
    SCU_LVDIFS_High(); //LVD低电压检测//高电平检测
    SCU_LVDVS_3V6();   //LVD休眠电压3.6V
    SCU_LVDFLT_Enable(); //LVD滤波使能
    SCU_LVDIT_Enable(); //LVD中断使能
    SCU_LVD_Enable();   //LVD使能
    SCU->PWRC.PORRSTF = 0;   //需要检测SOFT_RSTF标识需先将PORRSTF清零//上电复位标志
    SCU_RegLock();  //scu写保护上锁

    if (SCU_GetLVDFlagStatus(SCU_LVDFlag_Out) == SET) //LVD检测到电压低于4V
    {
        sleep(); //进入休眠函数
    }

    //以下开始进行主循环初始化
    SCU_RegUnLock();
    SCU_LVDIFS_Rise(); //LVD电压降低检测//上升沿检测
    NVIC_Init(NVIC_LVD_IRQn, NVIC_Priority_0, Enable); //LVD中断设置//中断优先级设为最高
    SCU_RegLock();



    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func0;
    x.Dir = GPIO_Direction_Output;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PDE = GPIO_PDE_Input_Disable;
    x.PUE = GPIO_PUE_Input_Disable;
    GPIO_Init(GPIO_Pin_A23, &x); //PA23配置为输出
    GPIO_SetBit(GPIO_Pin_A6);
    GPIO_Init(GPIO_Pin_A6, &x); //PA23配置为输出

    if (SCU->PWRC.SOFT_RSTF == 0) //程序没有经历过软复位
    {
        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转

        for (i = 0; i < 165350; i++);

        GPIO_ToggleBit(GPIO_Pin_A6);   //PA6翻转
    }

    //for(i=0; i<655350; i++);

    while (1)
    {
        //NVIC_SystemReset();
        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
        WDT_Clear();  //清狗

        if (g_sleep_flag == 1)  //LVD中断检测到VDD电压低于3.6V，则复位进入休眠函数
        {
            NVIC_SystemReset();
        }
    }
}
