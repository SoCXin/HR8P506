/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  sleep.c
*作  者:
*版  本:  V1.01
*日  期:  2018/03/26
*描  述:  休眠函数
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "sleep.h"

/***************************************************************
 函数名：void sleep(void)
 描  述：休眠函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void sleep(void)
{
    GPIO_InitSettingType y;
    KINT_InitSettingType z;
    __disable_irq(); //关闭IRQ总中断
    WDT_Clear();  //清狗
    DeviceClockAllEnable();

    GPIO->PAINEB.Word = 0XFFFFFFFF; //输入关闭
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //输出打开
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00000040;  //PA6输出高关闭LED1
    GPIO->PBDATA.Word = 0X00000080;  //PB7有上拉电阻

    y.Signal = GPIO_Pin_Signal_Digital;
    y.Func = GPIO_Reuse_Func0;
    y.Dir = GPIO_Direction_Input;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &y);


    z.IE_Set = KINT_IE_Set_Enable;
    z.Trigger_Style = KINT_Trigger_Trailing_Edge;
    KINT_Init(GPIO_Pin_A22, &z);                     //初始化按键中断

    SCU_RegUnLock();
    SCU_LVDVS_4V();    //LVD唤醒电压4V
    SCU_LVDIFS_Fall(); //LVD电压升高检测
    SCU_LVDFLT_Enable(); //LVD滤波使能
    SCU_LVD_Enable(); //LVD中断使能
    SCU->WAKEUPTIME.MOSC_EN = 0; //深睡眠下时钟自动关闭
    SCU->WAKEUPTIME.WAKEUPTIME = 20; //唤醒时间不可小于40us
    SCB_SystemLPConfig(SCB_LP_SleepDeep, Enable);  //深度睡眠模式
    SCU_RegLock();


    WDT_RegUnLock();//WDT关闭写保护
    WDT_ITEnable(); //IE使能

    NVIC_EnableIRQ(LVD_IRQn);  //使能LVD唤醒源
    NVIC_EnableIRQ(WDT_IRQn);  //使能WDT唤醒源
    NVIC_EnableIRQ(KINT_IRQn); //使能按键唤醒


    while (1) //休眠主循环
    {
        SCU_RegUnLock();
        SCU->SCLKEN0.SYSCLK_DIV = 5;// 系统时钟后分频1:32 //系统时钟周期不可小于2us
        NVIC->ICPR[0] = 0XFFFFFFFF; //清NVIC挂起标识
        __NOP();
        __NOP();
        __WFI(); //休眠
        __NOP();
        __NOP();
        SCU->SCLKEN0.SYSCLK_DIV = 0;// 恢复系统时钟后分频比
        SCU_RegLock();


        if (WDT_GetFlagStatus() != RESET)
        {
            WDT_Clear();  //清狗
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
        }

        if (SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET) //LVD唤醒
        {
            SCU_RegUnLock();
            SCU_LVDClearIFBit();
            SCU_RegLock();
            NVIC_SystemReset();   //复位唤醒
        }

        if (KINT_GetITFlag(GPIO_Pin_A22) != RESET)  //KINT唤醒
        {
            KINT_ClearITFlag(GPIO_Pin_A22);      // 清除按键中断标志位
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23翻转
        }
    }
}
