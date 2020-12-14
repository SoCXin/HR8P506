/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  LIGHT指示灯流水显示
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t Flag = 0;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();

    while (1)
    {
        switch (Flag)
        {
            case 0:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* 输出低电平，点亮LED */
                break;

            case 1:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* 输出低电平，点亮LED */
                break;

            case 2:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 3:
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 4:
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 5:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 6:
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 7:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 8:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* 输出低电平，点亮LED */
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 9:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* 输出低电平，点亮LED */
                break;

            case 10:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            default:
                break;
        }

        Flag = (Flag + 1) % 11;
        Delay_100us(2000);
    }
}
