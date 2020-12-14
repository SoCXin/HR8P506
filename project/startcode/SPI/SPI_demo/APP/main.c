/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  �ڲ�Flash��ʾ������
          FALSHģ�����ݴ洢������ַ��Χ0x00006400 ~ 0x000067FF
          ����ѡ���ַ���д������LED��ʾ�����1�ֽڵ�ַ+1�ֽ����ݣ�
         ��1������K4����ַ�Ͱ��ֽ�+1��ͬʱ������ǰ����
         ��2������K3����ַ�߰��ֽ�+1��ͬʱ������ǰ����
         ��3������K2��д������=��ǰ��ַ
         ��4������K1��д������=0x00
         ��5������K5��ȫƬ����=0xFF����Ҫ�����İ������ñ��̽�ZERO��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{
    uint8_t rbuf[4];
    uint8_t wbuf[4];

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    T16N3Init();
    KeyInit();
    SPI1Init();
    LEDInit();

    g_2ms_flag = 0;
    g_10ms_flag = 0;
    g_2ms_cnt = 0;
    g_key_cmd = 0;
    flag = 0;

    com = 0;                                        //��ʼ����ʾλ
    addr_h = 0x00;                                  //��ʼ����ַ
    addr_l = 0x00;
    addr = (addr_h << 4) + addr_l;
    data_h = 0x00;                                  //��ʼ������    data_l = 0x00;
    data = (data_h << 4) + data_l;

    SPI1ReadData(0, rbuf, 1);                       //����1���ֽ�EEPROM����

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);    //ˢ��LED��ʾ����
            com++;

            if (com > 3)
                com = 0;
        }

        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;
            g_key_cmd = KeyGetValue();

            switch (g_key_cmd)
            {
                case 1:
                    wbuf[0] = 0x00;
                    SPI1WriteData(addr, wbuf, 1);
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                case 2:
                    wbuf[0] = addr;
                    SPI1WriteData(addr, wbuf, 1);
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                case 3:
                    addr_h += 0x01;

                    if (addr_h > 0x07)
                        addr_h = 0;

                    addr = (addr_h << 4) + addr_l;
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                case 4:
                    addr_l += 0x01;

                    if (addr_l > 0x0F)
                        addr_l = 0;

                    addr = (addr_h << 4) + addr_l;
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                case 5:
                    SPI1EraseAll();
                    addr_h = 0x00;                      //��ַ����
                    addr_l = 0x00;
                    addr   = 0x00;
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                default:
                    g_key_cmd = 0;
                    break;
            }

            data_l = rbuf[0] & 0x0F;                //���¶�������
            data_h = (rbuf[0] >> 4);

            g_led_buf[0] = addr_h;                  //������ʾ����
            g_led_buf[1] = addr_l;
            g_led_buf[2] = data_h;
            g_led_buf[3] = data_l;
        }
    }
}
