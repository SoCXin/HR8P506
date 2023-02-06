/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  sleep.c
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/05/21
*描  述:  休眠函数
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "sleep.h"

/***************************************************************
 函数名：void light_sleep(void)
 描  述：进入浅睡眠
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void light_sleep(void)
{
    SCB_SystemLPConfig(SCB_LP_SleepDeep, Disable);      /* 浅睡眠 */
    SCB_SystemLPConfig(SCB_LP_SleepOnExit, Disable);    /* 从ISR中断处理程序返回到线程模式时不进入休眠 */
    SCB_SystemLPConfig(SCB_LP_SEVOPend, Enable);        /* 中断挂起作为唤醒事件 */

    __NOP();
    __NOP();
    __WFI(); /* 休眠 */
    __NOP();
    __NOP();
}

/***************************************************************
 函数名：void deep_sleep(void)
 描  述：进入深度睡眠
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void deep_sleep(void)
{   
    SCU_RegUnLock();
    SCU->WAKEUPTIME.WAKEUPTIME = 0xA50; //唤醒时间不可小于55us
    SCU->WAKEUPTIME.MOSC_EN = 0; // 自动关闭HRC、PLL、XTAL和时钟滤波器CLKFLT
    SCU->WAKEUPTIME.CLKFLT_EN = 0;// 禁止系统时钟滤波器使能
    SCU->WAKEUPTIME.FLASHPW_PD = 0;//  开启Flash电源控制位
    SCU->WAKEUPTIME.LDOLP_VOSEL = 4;// LDO电压输出1.4V

    SCB_SystemLPConfig(SCB_LP_SleepDeep, Enable);       /* 深度睡眠 */
    SCB_SystemLPConfig(SCB_LP_SleepOnExit, Disable);    /* 从ISR中断处理程序返回到线程模式时不进入休眠 */
    SCB_SystemLPConfig(SCB_LP_SEVOPend, Enable);        /* 中断挂起作为唤醒事件 */
    SCU_RegLock();

    __NOP();
    __NOP();
    __WFI(); /* 休眠 */
    __NOP();
    __NOP();
}
