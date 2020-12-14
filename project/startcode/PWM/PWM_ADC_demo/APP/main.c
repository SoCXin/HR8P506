/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.02
*日  期:  2017/06/29
*描  述:  PWM触发ADC示例程序
            在PA6、PA7引脚输出PWM波形，使用PWM调制模式触发ADC，采用10K的电位器，通过4位数码管显示ADC结果（12bits）
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint16_t ad_temp;

int main(void)
{
    uint16_t sum;
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemInit();
    DeviceClockAllEnable();

    LEDInit();
    ADCInit();
    T16N3Init();
    T16NxInit();

    while (1)
    {
        if (g_500ms_flag == 1)
        {
            g_500ms_flag = 0;
            sum = ad_temp;
            DispHextoBcd(sum, g_led_buf);
            ad_temp = 0;

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

