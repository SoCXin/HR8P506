/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ��������ʾ������
         ��1������K4�����ࡶ��ֻ�ϻ���
         ��2������K3�����ࡶ����á�
         ��3������K2�����ࡶ��ˢ����
         ��4������K1�����ࡶ���ܲ���
         ��5������K5�������������ף���Ҫ�����İ������ñ��̽�ZERO��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint32_t key;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    Buzzer_Init();
    KeyInit();

    while (1)
    {
        key = KeyGetValue();        /* ��ȡ����ֵ */

        switch (key)                /* ���ݰ���ֵ�����Ŷ�Ӧ������ */
        {
            case 5:
                PlayTone();
                break;

            case 4:
                PlayMusic(Music4);
                break;

            case 3:
                PlayMusic(Music3);
                break;

            case 2:
                PlayMusic(Music2);
                break;

            case 1:
                PlayMusic(Music1);
                break;

            default:
                break;
        }

        Delay10ms(2);               /* �������ֺ���ʱһ��� */
    }
}
