/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  FLASH IAP����
            FLASH��0x7Cҳд����0x12345678
            ��ȡ�ĵ�ַ�����Ƿ�д�룬д��ɹ����LD1��ʧ�ܵ��LD4
*��  ע:  оƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint32_t data = 0x12345678;
    uint32_t rbuf = 0;

    SystemInit();
    DeviceClockAllEnable();

    LightInit();

    IAP_PageErase(START_ADDR);
    IAPRead(&rbuf, START_ADDR, 1);

    IAP_WordProgram(START_ADDR, data);
    IAPRead(&rbuf, START_ADDR, 1);

    GPIO_WriteBit(GPIO_Pin_A6, 1);
    GPIO_WriteBit(GPIO_Pin_A7, 1);
    GPIO_WriteBit(GPIO_Pin_A8, 1);
    GPIO_WriteBit(GPIO_Pin_A9, 1);

    while (1)
    {
        if (data == rbuf)
        {
            GPIO_WriteBit(GPIO_Pin_A6, 0);
        }
        else
        {
            GPIO_WriteBit(GPIO_Pin_A9, 0);
        }
    }
}

