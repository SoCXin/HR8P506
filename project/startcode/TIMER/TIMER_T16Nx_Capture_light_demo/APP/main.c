/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:   Liut
*版  本:  V1.01
*日  期:  2017/06/30
*描  述:  16位引脚捕捉器示例程序
          PB0引脚输入上升沿方波信号，T16N3每捕获2次发生中断一次，捕捉值读入buffer
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint32_t count00 = 0;
uint32_t buf00[50];

int main(void)
{
    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    T16N3CAP_Init();                //PB0输入

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1);
}

