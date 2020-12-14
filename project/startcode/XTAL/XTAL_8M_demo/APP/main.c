/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  XTAL程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

//注：使用前使用JlinkBurner修改配置字CFG_OSC_PIN（默认使用PB8，PB9，8M晶振即可）
//注：此处测试需要PB8，PB9焊接8M晶振，不要使用母板（母板连接线路会对晶振产生影响），只需要使用子板即可

int main(void)
{
    SystemInit();
    SCU_OpenXTAL();
    SCU_SysClkSelect(SCU_CLK_XTAL);
    SystemCoreClock = 8000000;          //其他规格晶振在此处修改即可
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();

    while (1)
    {
        GPIO_WriteBit(GPIO_Pin_A6, 1);
        Delay_100us(2000);
        GPIO_WriteBit(GPIO_Pin_A6, 0);
        Delay_100us(2000);
    }
}
