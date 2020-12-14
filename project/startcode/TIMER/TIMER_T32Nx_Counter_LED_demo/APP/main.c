/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  32位计数器示例程序
            PB0引脚输入下降沿方波信号，LED显示输入方波的频率，最大显示支持9999Hz
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main(void)
{
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemInit();
    DeviceClockAllEnable();

    LightInit();
    LEDInit();
    T32N0CNT_Init();
    T16N2Init();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {
        if (g_1s_flag == 1)
        {
            g_1s_flag = 0;
            DispHextoBcd(count, g_led_buf);
            count = 0;
        }

        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);
            com++;

            if (com > 3)
                com = 0;
        }
    }
}

