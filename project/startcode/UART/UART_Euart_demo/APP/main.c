/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������
        �ϵ緢�� "Hello world!"�󣬵ȴ����ڽ��գ�������ͬByte
*��  ע:  оƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t i;
    uint8_t buf[] = {"Hello world!"};    //�������ݻ���

    SystemInit();
    DeviceClockAllEnable();

    EUARTInit();                         //UART��ʼ��(9600,8,NO,1)

    for (i = 0; i < sizeof(buf); i++)
    {
        EUART_SendByte(buf[i]);

        while (EUART_GetFlagStatus(EUART_FLAG_TC) == RESET);

        EUART_ClearITPendingBit(EUART_CLR_TC);
    }

    while (1);                          //�жϽ��н������ݺͷ���
}



