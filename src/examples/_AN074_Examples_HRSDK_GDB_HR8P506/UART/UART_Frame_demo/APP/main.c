/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:    main.c
*作  者:    Liut
*版  本:    V1.01
*日  期:    2017/06/29
*描  述:    UART演示主程序
            定义了串口通信主机请求/从机应答的通讯协议
            通讯协议如下：
            数据帧头1（固定）    0x55
            数据帧头2（固定）    0xAA
            设备地址（Addr）     0x01
            功能代码（Func）     1～255
            数据字节（N个）      DataN
            校验码（异或和）     = 0x55 ^ 0xAA ^ Addr ^ Func ^ Data1 ^ … ^ DataN
            数据帧尾1（固定）    0x5A
            数据帧尾2（固定）    0xA5
            按照协议，HRSDK接收上位机发送的数据帧，应答同样的数据帧
            LED数码管显示数据帧中的功能代码和第1个字节数据
            例如：
            55 AA 01 45 41 53 54 53 4F 46 54 F3 5A A5
*备  注:    
            本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint32_t i;
    uint8_t com;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    T16N3Init();
    LEDInit();
    UARTInit();

    com = 0;
    g_2ms_flag = 0;
    g_10ms_flag = 0;
    g_2ms_cnt  = 0;

    g_data1_h = 0x00;                                   //初始化接收数据，帧中功能码
    g_data1_l = 0x00;
    g_data1 = (g_data1_h << 4) + g_data1_l;

    g_data2_h = 0x00;                                   //初始化接收数据，帧中第1个数据
    g_data2_l = 0x00;
    g_data2 = (g_data2_h << 4) + g_data2_l;

    g_tx_length = 0;                                    //发送数据长度
    g_tx_count = 0;                                     //发送字节计数
    g_rx_length = 0;                                    //接收数据长度
    g_rx_count = 0;                                     //接收字节计数
    g_rx_time = 0;                                      //接收计时
    g_rx_finish_flag = 0;                               //接收完成标志
    g_rx_start_flag = 0;                                //接收起始标志

    g_txbuf[3] = 'E';
    g_txbuf[4] = 'A';
    g_txbuf[5] = 'S';
    g_txbuf[6] = 'T';
    g_txbuf[7] = 'S';
    g_txbuf[8] = 'O';
    g_txbuf[9] = 'F';
    g_txbuf[10] = 'T';

    g_tx_length = 14;
    UARTTxData(g_txbuf, g_tx_length);                   //发送数据帧“EASTSOFT”

    while (1)
    {
        if (1 == g_rx_finish_flag)
        {
            g_rx_finish_flag = 0;
            g_rx_length = g_rx_count;
            g_rx_count = 0;
            g_tx_length = g_rx_length;

            if (0 == UARTRxData(g_rxbuf, g_rx_length))  //接收数据帧
            {
                g_tx_length = g_rx_length;              //赋值发送长度，等同接收数据长度

                for (i = 3; i < g_tx_length - 3; i++)   //准备发送数据（功能码+数据内容）
                    g_txbuf[i] = g_rxbuf[i];            //等同于接收数据内容

                UARTTxData(g_txbuf, g_tx_length);       //发送数据帧
            }
        }

        if (1 == g_2ms_flag)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);        //刷新LED显示数据
            com++;

            if (com > 3)
                com = 0;
        }

        if (1 == g_10ms_flag)
        {
            g_10ms_flag = 0;

            g_data1_l = g_rxbuf[3] & 0x0F;              //更新接收数据（功能码）
            g_data1_h = g_rxbuf[3] >> 4;
            g_data2_l = g_rxbuf[4] & 0x0F;              //更新接收数据（第1个数据字节）
            g_data2_h = g_rxbuf[4] >> 4;

            g_led_buf[0] = g_data1_h;                   //更新显示缓存
            g_led_buf[1] = g_data1_l;
            g_led_buf[2] = g_data2_h;
            g_led_buf[3] = g_data2_l;
        }
    }
}
