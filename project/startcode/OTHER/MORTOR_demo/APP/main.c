/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/07/13
*��  ��:  ���������ʾ������
          ��������ͺţ�28BYJ-48��������ʽΪ4��8��
          K5�����л��������״̬����ת-ֹͣ-��ת-ֹͣ����Ҫ�����İ������ñ��̽�ZERO��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

const uint8_t MotorClockWiseRotation[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    // ���������ת��
const uint8_t MotorNotClockWiseRotation[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09}; // ���������ת��

int main(void)
{
    uint8_t mode;
    uint8_t step;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    MotorInit();
    KeyInit();

    mode = 0;
    step = 0;

    while (1)
    {
        /* ���Ƶ����ת */
        switch (mode)
        {
        case 0:                                         //��ת
            MotorWrite(MotorClockWiseRotation[step]);
            step++;
            if (step >= 8)
                step = 0;
            Delay_100us(11);
            break;
        case 1:                                         //ֹͣ
            break;
        case 2:                                         //��ת
            MotorWrite(MotorClockWiseRotation[step]);
            if (step > 0)
                step--;
            else
                step = 7;
            Delay_100us(11);
            break;
        case 3:                                         //ֹͣ
            break;
        default:
            break;
        }

        /* ��ȡ������Ϣ */
        if (5 == KeyGetValue())                         //�жϰ����Ƿ���K5
        {
            if (mode == 0)
            {
                if (step == 0)
                    step = 6;
                else if (step == 1)
                    step = 7;
                else
                    step -= 2;
            }
            else if (mode == 2)
            {
                if (step == 7)
                    step = 1;
                else if (step == 6)
                    step = 0;
                else
                    step += 2;
            }

            mode = (mode + 1) % 4;
        }
    }
}
