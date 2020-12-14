/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:    main.c
*��  ��:    Liut
*��  ��:    V1.01
*��  ��:    2017/06/29
*��  ��:    UART��ʾ������
            �����˴���ͨ����������/�ӻ�Ӧ���ͨѶЭ��
            ͨѶЭ�����£�
            ����֡ͷ1���̶���    0x55
            ����֡ͷ2���̶���    0xAA
            �豸��ַ��Addr��     0x01
            ���ܴ��루Func��     1��255
            �����ֽڣ�N����      DataN
            У���루���ͣ�     = 0x55 ^ 0xAA ^ Addr ^ Func ^ Data1 ^ �� ^ DataN
            ����֡β1���̶���    0x5A
            ����֡β2���̶���    0xA5
            ����Э�飬HRSDK������λ�����͵�����֡��Ӧ��ͬ��������֡
            LED�������ʾ����֡�еĹ��ܴ���͵�1���ֽ�����
            ���磺
            55 AA 01 45 41 53 54 53 4F 46 54 F3 5A A5
*��  ע:    
            ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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

    g_data1_h = 0x00;                                   //��ʼ���������ݣ�֡�й�����
    g_data1_l = 0x00;
    g_data1 = (g_data1_h << 4) + g_data1_l;

    g_data2_h = 0x00;                                   //��ʼ���������ݣ�֡�е�1������
    g_data2_l = 0x00;
    g_data2 = (g_data2_h << 4) + g_data2_l;

    g_tx_length = 0;                                    //�������ݳ���
    g_tx_count = 0;                                     //�����ֽڼ���
    g_rx_length = 0;                                    //�������ݳ���
    g_rx_count = 0;                                     //�����ֽڼ���
    g_rx_time = 0;                                      //���ռ�ʱ
    g_rx_finish_flag = 0;                               //������ɱ�־
    g_rx_start_flag = 0;                                //������ʼ��־

    g_txbuf[3] = 'E';
    g_txbuf[4] = 'A';
    g_txbuf[5] = 'S';
    g_txbuf[6] = 'T';
    g_txbuf[7] = 'S';
    g_txbuf[8] = 'O';
    g_txbuf[9] = 'F';
    g_txbuf[10] = 'T';

    g_tx_length = 14;
    UARTTxData(g_txbuf, g_tx_length);                   //��������֡��EASTSOFT��

    while (1)
    {
        if (1 == g_rx_finish_flag)
        {
            g_rx_finish_flag = 0;
            g_rx_length = g_rx_count;
            g_rx_count = 0;
            g_tx_length = g_rx_length;

            if (0 == UARTRxData(g_rxbuf, g_rx_length))  //��������֡
            {
                g_tx_length = g_rx_length;              //��ֵ���ͳ��ȣ���ͬ�������ݳ���

                for (i = 3; i < g_tx_length - 3; i++)   //׼���������ݣ�������+�������ݣ�
                    g_txbuf[i] = g_rxbuf[i];            //��ͬ�ڽ�����������

                UARTTxData(g_txbuf, g_tx_length);       //��������֡
            }
        }

        if (1 == g_2ms_flag)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);        //ˢ��LED��ʾ����
            com++;

            if (com > 3)
                com = 0;
        }

        if (1 == g_10ms_flag)
        {
            g_10ms_flag = 0;

            g_data1_l = g_rxbuf[3] & 0x0F;              //���½������ݣ������룩
            g_data1_h = g_rxbuf[3] >> 4;
            g_data2_l = g_rxbuf[4] & 0x0F;              //���½������ݣ���1�������ֽڣ�
            g_data2_h = g_rxbuf[4] >> 4;

            g_led_buf[0] = g_data1_h;                   //������ʾ����
            g_led_buf[1] = g_data1_l;
            g_led_buf[2] = g_data2_h;
            g_led_buf[3] = g_data2_l;
        }
    }
}
