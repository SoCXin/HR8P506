/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LIGHTָʾ����ˮ��ʾ
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* ����͵�ƽ������LED */
                break;

            case 1:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* ����͵�ƽ������LED */
                break;

            case 2:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 3:
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 4:
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* ����͵�ƽ������LED */
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
                GPIO_WriteBit(GPIO_Pin_A6, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 7:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 8:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 0);  /* ����͵�ƽ������LED */
                GPIO_WriteBit(GPIO_Pin_A9, 1);
                break;

            case 9:
                GPIO_WriteBit(GPIO_Pin_A6, 1);
                GPIO_WriteBit(GPIO_Pin_A7, 1);
                GPIO_WriteBit(GPIO_Pin_A8, 1);
                GPIO_WriteBit(GPIO_Pin_A9, 0);  /* ����͵�ƽ������LED */
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
