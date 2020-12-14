/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  IIC������ʾ������
          IIC�շ�����ʹ��ɨ�跽ʽ--EEPROM�ͺţ�24C01�����ʵ�ַ��Χ0x00~0x7F
          ����ѡ���ַ���д������LED��ʾ�����1�ֽڵ�ַ+1�ֽ����ݣ�
         ��1������K4����ַ�Ͱ��ֽ�+1��ͬʱ������ǰ����
         ��2������K3����ַ�߰��ֽ�+1��ͬʱ������ǰ����
         ��3������K2��д������=��ǰ��ַ
         ��4������K1��д������=0x00
         ��5������K5��ȫƬ��������Ҫ�����İ������ñ��̽�ZERO��
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{
    uint8_t rbuf[4];
    uint8_t wbuf[4];
    int i;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    T16N3Init();
    KeyInit();
    IIC0_MasterInit();
    LEDInit();

    g_2ms_flag = 0;
    g_10ms_flag = 0;
    g_2ms_cnt = 0;
    g_key_cmd = 0;
    flag = 0;
    com = 0;

    addr_h = 0x00;                                                  //��ʼ����ַ
    addr_l = 0x00;
    addr = (addr_h << 4) + addr_l;
    data_h = 0x00;                                                  //��ʼ������
    data_l = 0x00;
    data = (data_h << 4) + data_l;

    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);                    //ˢ��LED��ʾ����
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
                case 1:                                                 // write 0x00
                    wbuf[0] = 0x00;
                    IIC0_MasterWriteData(SLAVE_ADDR, addr, wbuf, 1);    //д��1���ֽ�EEPROM����
                    Delay_100us(100);
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                case 2:                                                 // write current addr
                    wbuf[0] = addr;
                    IIC0_MasterWriteData(SLAVE_ADDR, addr, wbuf, 1);    //д��1���ֽ�EEPROM����
                    Delay_100us(100);
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                case 3:
                    addr_h += 0x01;

                    if (addr_h > 0x07)
                        addr_h = 0;

                    addr = (addr_h << 4) + addr_l;
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                case 4:
                    addr_l += 0x01;

                    if (addr_l > 0x0F)
                        addr_l = 0;

                    addr = (addr_h << 4) + addr_l;
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                case 5:
                    addr_l = 0;
                    addr_h = 0;
                    addr = (addr_h << 4) | addr_l;

                    for (i = 0; i < 16; ++i)
                    {
                        IIC0_MasterErasePage(SLAVE_ADDR, addr);         //����128���ֽ�EEPROM�ռ䣬д0xFF
                        Delay_100us(100);
                        addr += 8;
                    }

                    addr_l = 0;
                    addr_h = 0;
                    addr = (addr_h << 4) | addr_l;
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                default:
                    g_key_cmd = 0;
                    break;
            }

            data_l = rbuf[0] & 0x0F;                                //���¶�������
            data_h = (rbuf[0] >> 4);

            g_led_buf[0] = addr_h;                                  //������ʾ����
            g_led_buf[1] = addr_l;
            g_led_buf[2] = data_h;
            g_led_buf[3] = data_l;
        }
    }
}
