/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LVD示例程序：拨码开关由5V切换到3.3V时，LVD检测低于4V电压，再切换回5V后，则点亮LED1-LED4
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    SCU_RegUnLock();
    SCU_LVDVS_4V();
    SCU_LVDIFS_Fall();
    SCU_LVDFLT_Enable();
    NVIC_Init(NVIC_LVD_IRQn, NVIC_Priority_0, Enable); //中断设置
    SCU_LVD_Enable();
    SCU_LVDIT_Enable();
    SCU_RegLock();

    while (1);
}
