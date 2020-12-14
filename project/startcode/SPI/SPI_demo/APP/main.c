/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  内部Flash演示主程序
          FALSH模拟数据存储器，地址范围0x00006400 ~ 0x000067FF
          按键选择地址或读写操作，LED显示结果（1字节地址+1字节数据）
         （1）单击K4：地址低半字节+1，同时读出当前数据
         （2）单击K3：地址高半字节+1，同时读出当前数据
         （3）单击K2：写入数据=当前地址
         （4）单击K1：写入数据=0x00
         （5）长按K5：全片擦除=0xFF（需要将核心板的跳线帽插短接ZERO）
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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

    com = 0;                                        //初始化显示位
    addr_h = 0x00;                                  //初始化地址
    addr_l = 0x00;
    addr = (addr_h << 4) + addr_l;
    data_h = 0x00;                                  //初始化数据    data_l = 0x00;
    data = (data_h << 4) + data_l;

    SPI1ReadData(0, rbuf, 1);                       //读出1个字节EEPROM数据

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);    //刷新LED显示数据
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
                    addr_h = 0x00;                      //地址回零
                    addr_l = 0x00;
                    addr   = 0x00;
                    SPI1ReadData(addr, rbuf, 1);
                    break;

                default:
                    g_key_cmd = 0;
                    break;
            }

            data_l = rbuf[0] & 0x0F;                //更新读出数据
            data_h = (rbuf[0] >> 4);

            g_led_buf[0] = addr_h;                  //更新显示缓存
            g_led_buf[1] = addr_l;
            g_led_buf[2] = data_h;
            g_led_buf[3] = data_l;
        }
    }
}
