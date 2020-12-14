/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  yuzr
*版  本:  V1.00
*日  期:  2017/10/17
*描  述:  7816演示实验，初始化ESAM模并复位ESAM，接收ESAM复位应答数据，
                    向ESAM写入测试命令，正确执行命令则LED亮
*备  注:          PB04--IC_IO   PB05--IC_CLK  PB07--IC_RST   PA06--LED
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"



/*********************************************************
函数名: main
描  述: 主函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
int main(void)
{
    uint8_t ret = 0;
    uint8_t  IC_Ret_Buff[13];    //应答数据缓存，一共13个字节

    SystemInit();                //系统设置，默认设置
    DeviceClockAllEnable();        //外设时钟设置
    led_init();                  //led初始化，PA06
    User_7816Init();                 //7816初始化
    LED_Dark;                    //熄灭LED1
    ResetRec(IC_Ret_Buff);      //复位并读取复位数据
    ret = Instruction_Test();  //测试读写命令

    if (ret == SUCCESS)
    {
        LED_Light;                 //LED1点亮
    }

    while (1)
    {

    }
}
/*********************************************************
函数名: led_init
描  述: led初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void led_init(void)
{
    GPIO_InitSettingType x;
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Enable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(LED_PIN, &x);  //LED1 -- PA06
}
