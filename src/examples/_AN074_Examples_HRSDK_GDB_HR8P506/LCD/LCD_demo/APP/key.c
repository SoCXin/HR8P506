/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  key.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  Key模块程序
*备  注:  
          R1~R2行输出，L1~L2列输入
              |    L1    L2
            --|--------
            R1|    K2    K1
            R2|    K4    K3
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "key.h"

uint8_t key1_press_flag;
uint8_t key2_press_flag;
uint8_t key3_press_flag;
uint8_t key4_press_flag;
uint8_t key5_press_flag;

uint8_t key1_hold_time;
uint8_t key2_hold_time;
uint8_t key3_hold_time;
uint8_t key4_hold_time;
uint8_t key5_hold_time;

/*********************************************************
函数名: void KeyInit(void)
描  述: 按键初始化子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void KeyInit(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Enable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_B1, &x); // KL2
    GPIO_Init(GPIO_Pin_B0, &x); // KR2
    GPIO_Init(GPIO_Pin_A2, &x); // KL1
    GPIO_Init(GPIO_Pin_A3, &x); // KR2
    GPIO_Init(GPIO_Pin_B9, &x); // K5

    key1_press_flag = 0;
    key2_press_flag = 0;
    key3_press_flag = 0;
    key4_press_flag = 0;
    key5_press_flag = 0;

    key1_hold_time = 0;
    key2_hold_time = 0;
    key3_hold_time = 0;
    key4_hold_time = 0;
    key5_hold_time = 0;
}

/*********************************************************
函数名: uint8_t KeyGetValue(void)
描  述: 按键驱动子程序，判断按键状态，读取键值
输入值: 无
输出值: 无
返回值: 1 - K1（按下有效）
        2 - K2（释放有效）
        3 - K3（长按有效）
        4 - K4（复合K2有效）
**********************************************************/
uint8_t KeyGetValue(void)
{
    uint8_t temp_key_value = 0;
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A3, &x);             //设置KR1为输出
    __NOP();
    __NOP();
    GPIO_WriteBit(GPIO_Pin_A3, 0);          //KR1输出低电平

    if ((GPIO_ReadBit(GPIO_Pin_B1)) == 0)   //KL2==0?
    {
        if (key1_press_flag == 0)
        {
            key1_hold_time++;

            if (key1_hold_time >= 2)
            {
                key1_hold_time = 0;
                key1_press_flag = 1;
            }
        }
    }
    else
    {
        if (key1_press_flag == 1)
        {
            key1_hold_time++;

            if (key1_hold_time >= 2)
            {
                key1_hold_time = 0;
                key1_press_flag = 0;
                temp_key_value = 1;
            }
        }
    }

    if ((GPIO_ReadBit(GPIO_Pin_A2)) == 0)   //KL1==0?
    {
        if (key2_press_flag == 0)
        {
            key2_hold_time++;

            if (key2_hold_time >= 2)
            {
                key2_hold_time = 0;
                key2_press_flag = 1;
            }
        }
    }
    else
    {
        if (key2_press_flag == 1)
        {
            key2_hold_time++;

            if (key2_hold_time >= 2)
            {
                key2_hold_time = 0;
                key2_press_flag = 0;
                temp_key_value = 2;
            }
        }
    }

    GPIO_WriteBit(GPIO_Pin_A3, 1);          //KR1输出高电平

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A3, &x);             //设置KR1为输入
    __NOP();
    __NOP();

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &x);             //设置KR2为输出
    __NOP();
    __NOP();

    GPIO_WriteBit(GPIO_Pin_B0, 0);          //KR2输出低电平

    if ((GPIO_ReadBit(GPIO_Pin_B1)) == 0)   //KL2==0?
    {
        if (key3_press_flag == 0)
        {
            key3_hold_time++;

            if (key3_hold_time >= 2)
            {
                key3_hold_time = 0;
                key3_press_flag = 1;
            }
        }
    }
    else
    {
        if (key3_press_flag == 1)
        {
            key3_hold_time++;

            if (key3_hold_time >= 2)
            {
                key3_hold_time = 0;
                key3_press_flag = 0;
                temp_key_value = 3;
            }
        }
    }

    if ((GPIO_ReadBit(GPIO_Pin_A2)) == 0)   //KL1==0?
    {
        if (key4_press_flag == 0)
        {
            key4_hold_time++;

            if (key4_hold_time >= 2)
            {
                key4_hold_time = 0;
                key4_press_flag = 1;
            }
        }
    }
    else
    {
        if (key4_press_flag == 1)
        {
            key4_hold_time++;

            if (key4_hold_time >= 2)
            {
                key4_hold_time = 0;
                key4_press_flag = 0;
                temp_key_value = 4;
            }
        }
    }

    GPIO_WriteBit(GPIO_Pin_B0, 1);          //KR2输出高电平

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &x);             //设置KR2为输入
    __NOP();
    __NOP();

    if ((GPIO_ReadBit(GPIO_Pin_B9)) == 0)   //K5==0?
    {
        if (key5_press_flag == 0)
        {
            key5_hold_time++;

            if (key5_hold_time >= 2)
            {
                key5_hold_time = 0;
                key5_press_flag = 1;
            }
        }
    }
    else
    {
        if (key5_press_flag == 1)
        {
            key5_hold_time++;

            if (key5_hold_time >= 2)
            {
                key5_hold_time = 0;
                key5_press_flag = 0;
                temp_key_value = 5;
            }
        }
    }

    return temp_key_value;
}
