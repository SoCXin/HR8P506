/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  ADC演示主程序
          采用10K的电位器，通过4位数码管显示ADC结果（12bits），按键K1切换ADC通道，分别采样AIN1、AIN0--软件控制采样启停
*备  注:
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t KeyGetValue(void);
void ADC_Set_CH(ADC_TYPE_CHS AdcCH);

int main()
{
    uint16_t sum;
    uint8_t g_led_buf[4];
    uint8_t com;
    uint8_t channel_flag = 0;

    com = 0;
    sum = 0;

    SystemInit();
    T16N3Init();
    LEDInit();
    ADCInit();

    while (1)
    {
        if (channel_flag == 0)                          //选择通道1
        {
            ADC_Set_CH(ADC_CHS_AIN1);
        }
        else                                            //选择通道0
        {
            ADC_Set_CH(ADC_CHS_AIN0);
        }

        if (g_500ms_flag == 1)
        {
            g_500ms_flag = 0;
            sum = ADCRead();
            DispHextoBcd(sum, g_led_buf);
        }

        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);
            com++;

            if (com > 3)
                com = 0;
        }

        if (1 == g_10ms_flag)                           //间隔10ms扫描按键
        {
            g_10ms_flag = 0;

            if (1 == KeyGetValue())
            {
                channel_flag = ~channel_flag;       //切换ADC模拟通道
            }
        }
    }
}
