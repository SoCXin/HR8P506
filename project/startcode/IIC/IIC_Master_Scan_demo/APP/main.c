/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  IIC主机演示主程序
          IIC收发数据使用扫描方式--EEPROM型号：24C01，访问地址范围0x00~0x7F
          按键选择地址或读写操作，LED显示结果（1字节地址+1字节数据）
         （1）单击K4：地址低半字节+1，同时读出当前数据
         （2）单击K3：地址高半字节+1，同时读出当前数据
         （3）单击K2：写入数据=当前地址
         （4）单击K1：写入数据=0x00
         （5）单击K5：全片擦除（需要将核心板的跳线帽插短接ZERO）
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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

    addr_h = 0x00;                                                  //初始化地址
    addr_l = 0x00;
    addr = (addr_h << 4) + addr_l;
    data_h = 0x00;                                                  //初始化数据
    data_l = 0x00;
    data = (data_h << 4) + data_l;

    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);                    //刷新LED显示数据
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
                    IIC0_MasterWriteData(SLAVE_ADDR, addr, wbuf, 1);    //写入1个字节EEPROM数据
                    Delay_100us(100);
                    IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);
                    break;

                case 2:                                                 // write current addr
                    wbuf[0] = addr;
                    IIC0_MasterWriteData(SLAVE_ADDR, addr, wbuf, 1);    //写入1个字节EEPROM数据
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
                        IIC0_MasterErasePage(SLAVE_ADDR, addr);         //擦除128个字节EEPROM空间，写0xFF
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

            data_l = rbuf[0] & 0x0F;                                //更新读出数据
            data_h = (rbuf[0] >> 4);

            g_led_buf[0] = addr_h;                                  //更新显示缓存
            g_led_buf[1] = addr_l;
            g_led_buf[2] = data_h;
            g_led_buf[3] = data_l;
        }
    }
}
