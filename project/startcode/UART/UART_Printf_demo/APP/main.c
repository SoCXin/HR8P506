/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������
         �ϵ緢�� "Hello world!"�󣬵ȴ����ڽ��գ�������ͬByte
                 ʹ��UART_printf����ǰ��Ҫ�����������裺
                 1��keil��ѡUse MicroLIB 2��main.c #include "stdio.h"��3��keil #define __PRINTF_USE_UART0__
*��  ע:  оƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "stdio.h"

int main(void)
{
    uint8_t cnt = 245;
    char buf[] = {'E', 'a', 's', 't', 's', 'o', 'f', 't', '!', '\0'};

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    UARTInit();                         //UART��ʼ��(9600,8,NO,1)

    while (1)
    {
        Delay_100us(10000);
        printf(" Hello world! \r\n");       //��ӡ�ַ���
        Delay_100us(10000);
        printf(" cnt = %d \r\n", cnt);     //��ӡ10������ֵ
        Delay_100us(10000);
        printf(" %s \r\n", buf);            //��ӡ�ַ�
    }

}



