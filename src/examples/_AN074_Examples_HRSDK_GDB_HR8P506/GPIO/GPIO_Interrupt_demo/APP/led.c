/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  led.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  LED显示程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "led.h"

const uint8_t LED7Code[CODEMAX] =
{
    0x3f, // 0
    0x30, // 1
    0x5b, // 2
    0x4F, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6F, // 9
    0x77, // a
    0x7c, // 6
    0x39, //c
    0x5e, //d
    0x79, //e
    0x71, //f
};

/***************************************************************
 函数名：void GPIOInit(void)
 描  述：GPIO口设置
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void GPIOInit(void)
{
    GPIO_InitSettingType x;
    GPIO_InitSettingType z;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable ;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable; 

    GPIO_Init(GPIO_Pin_A14, &x);
    GPIO_Init(GPIO_Pin_A15, &x);
    GPIO_Init(GPIO_Pin_A16, &x);
    GPIO_Init(GPIO_Pin_A17, &x);
    GPIO_Init(GPIO_Pin_A18, &x);
    GPIO_Init(GPIO_Pin_A19, &x);
    GPIO_Init(GPIO_Pin_A20, &x);
    GPIO_Init(GPIO_Pin_A21, &x);

    GPIO_Init(GPIO_Pin_A28, &x);
    GPIO_Init(GPIO_Pin_A29, &x);
    GPIO_Init(GPIO_Pin_A30, &x);
    GPIO_Init(GPIO_Pin_A31, &x);
    
    z.Dir = GPIO_Direction_Input;
    z.PUE = GPIO_PUE_Input_Enable;  
    
    GPIO_Init(GPIO_Pin_B9, &z);                      //初始化GPIO_PB9
}

/***************************************************************
函数名: LEDDisplayData(uint8_t com, uint8_t dat)
描  述: LED GPIO口设置
输入值: com 数码管位置
            dat 写入数码管数字
输出值: 无
返回值: 成功返回1
            失败返回-1
***************************************************************/
int32_t LEDDisplayData(uint8_t com, uint8_t dat)
{
    uint8_t seg;

    if (com >= COMMAX || dat >= CODEMAX)
    {
        return -1;
    }

    GPIO_WriteBit(GPIO_Pin_A28, 1);
    GPIO_WriteBit(GPIO_Pin_A29, 1);
    GPIO_WriteBit(GPIO_Pin_A30, 1);
    GPIO_WriteBit(GPIO_Pin_A31, 1);
    seg = LED7Code[dat];
    LEDDisplaySeg(seg);

    switch (com)
    {
        case 0:
            GPIO_WriteBit(GPIO_Pin_A28, 0);
            break;

        case 1:
            GPIO_WriteBit(GPIO_Pin_A29, 0);
            break;

        case 2:
            GPIO_WriteBit(GPIO_Pin_A30, 0);
            break;

        case 3:
            GPIO_WriteBit(GPIO_Pin_A31, 0);
            break;
    }

    return 1;
}

/***************************************************************
 函数名:    LEDDisplaySeg(uint8_t seg)
 描  述:  LED 将8bit填入数码管ABCDEFGH接口
 输入值:    seg 待填入8bit
 输出值:    无
 返回值:    无
***************************************************************/
void LEDDisplaySeg(uint8_t seg)
{
    //E D H C G B F A
    int32_t i;
    uint8_t post[8] = {GPIO_Pin_A14, GPIO_Pin_A16, GPIO_Pin_A18, GPIO_Pin_A20, GPIO_Pin_A21, GPIO_Pin_A15, GPIO_Pin_A17, GPIO_Pin_A19};

    for (i = 0; i < 8; i++)
    {
        if (seg & (1 << i))
        {
            GPIO_WriteBit((GPIO_Pin)(post[i]), 1);
        }
        else
        {
            GPIO_WriteBit((GPIO_Pin)(post[i]), 0);
        }
    }
}

/***************************************************************
 函数名:    LEDDisplaySeg(uint8_t seg)
 描  述:  LED 将8bit填入数码管ABCDEFGH接口
 输入值:    hex_data 16进制数
 输出值:    bcd_data 10进制数
 返回值:    成功返回1
                失败返回-1
***************************************************************/
int32_t DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data)
{
    uint32_t temp;
    uint32_t num;

    if (hex_data > 9999)
    {
        return -1;
    }

    temp = hex_data;
    num = temp / 1000;
    temp = temp % 1000;
    *(bcd_data + 0) = (uint8_t)num;

    num = temp / 100;
    temp = temp % 100;
    *(bcd_data + 1) = (uint8_t)num;

    num = temp / 10;
    temp = temp % 10;
    *(bcd_data + 2) = (uint8_t)num;
    *(bcd_data + 3) = (uint8_t)temp;

    return 1;
}
