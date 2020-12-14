/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  motor.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/07/13
*描  述:  步进电机驱动
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "motor.h"

/*********************************************************
函数名: void MotorInit(void)
描  述: 步进电机初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void MotorInit(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func0;
    x.Dir = GPIO_Direction_Output;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIO_Pin_A6, &x);
    GPIO_Init(GPIO_Pin_A7, &x);
    GPIO_Init(GPIO_Pin_A8, &x);
    GPIO_Init(GPIO_Pin_A9, &x);
}

/*********************************************************
函数名: void MotorWrite(uint8_t data)
描  述: 设置步进电机的下一个转动方向
输入值: data: 步进电机的下一个转动方向
输出值: 无
返回值: 无
**********************************************************/
void MotorWrite(uint8_t data)
{
    if (data & 0x01)
        GPIO_WriteBit(GPIO_Pin_A9, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A9, 0);

    if (data & 0x2)
        GPIO_WriteBit(GPIO_Pin_A8, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A8, 0);

    if (data & 0x4)
        GPIO_WriteBit(GPIO_Pin_A7, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A7, 0);

    if (data & 0x8)
        GPIO_WriteBit(GPIO_Pin_A6, 1);
    else
        GPIO_WriteBit(GPIO_Pin_A6, 0);

    return;
}
