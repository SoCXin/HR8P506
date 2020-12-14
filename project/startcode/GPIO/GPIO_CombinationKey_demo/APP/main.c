/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  按键检测演示主程序
*备  注:  
          单击K1（按下有效），LED1点亮
          单击K2（释放有效），LED2翻转
          单击K3（按下有效），LED1-LED4流水点亮
          单击K4（按下有效），LED4-LED1流水点亮
          单击K5（按下有效，核心板ZERO需要短接），所有LED全部熄灭
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    T16N3Init();
    LightInit();
    KeyInit();

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    g_10ms_flag = 0;
    g_200ms_flag = 0;
    g_200ms_cnt = 0;
    g_key_cmd = 0;
    flag = 0;

    while (1)
    {
        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;
            g_key_cmd = KeyGetValue();

            switch (g_key_cmd)
            {
                case 1:
                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    break;

                case 2:
                    if (flag == 1)
                    {
                        flag = 0;
                        GPIO_WriteBit(GPIO_Pin_A7, 1);
                    }
                    else
                    {
                        flag = 1;
                        GPIO_WriteBit(GPIO_Pin_A7, 0);
                    }

                    break;

                case 3:
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);

                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A7, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A8, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A9, 0);
                    Delay1ms(500);

                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);
                    break;

                case 4:
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A7, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    GPIO_WriteBit(GPIO_Pin_A9, 1);

                    GPIO_WriteBit(GPIO_Pin_A9, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A8, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A7, 0);
                    Delay1ms(500);
                    GPIO_WriteBit(GPIO_Pin_A6, 0);
                    Delay1ms(500);

                    GPIO_WriteBit(GPIO_Pin_A6, 1);
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

                default:
                    g_key_cmd = 0;
                    GPIO_WriteBit(GPIO_Pin_A6, 1);
                    GPIO_WriteBit(GPIO_Pin_A8, 1);
                    break;
            }
        }
    }
}
