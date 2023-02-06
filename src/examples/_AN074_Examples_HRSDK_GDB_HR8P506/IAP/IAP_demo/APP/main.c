/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  FLASH IAP例程
            FLASH的0x7C页写数据0x12345678
            读取改地址数据是否写入，写入成功点灯LD1，失败点灯LD4
*备  注:  芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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

